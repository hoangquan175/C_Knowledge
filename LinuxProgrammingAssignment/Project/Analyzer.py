import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import sys
import os
from typing import List, Tuple

# =========================
# CONFIG
# =========================

# Danh sách file input (có thể truyền nhiều file)
# Ưu tiên: dùng command-line args nếu có, fallback về list này
FILE_PATHS = [
    "log_1us.txt",
]

# Các chu kỳ mục tiêu (ns) — user tự config
TARGETS = [100]

# Tolerance ±% quanh target
TOL_RATIO = 2000

# =========================
# HELPERS
# =========================

def load_file(path: str) -> Tuple[np.ndarray, np.ndarray]:
    """
    Load file CSV/TXT có format:
        Current Time (ns), Interval (ns)
        1779898601507828599, 0
        ...
    Trả về (time_array, interval_array).
    """
    df = pd.read_csv(
        path,
        header=0,
        names=["time", "interval"],
        skipinitialspace=True,
    )
    return df["time"].values.astype(np.float64), df["interval"].values.astype(np.float64)


def filter_by_target(
    interval: np.ndarray, target: float, tol_ratio: float = 0.5
) -> np.ndarray:
    """Trả về boolean mask của các sample nằm trong [target*(1-tol), target*(1+tol)]."""
    lower = target * (1 - tol_ratio)
    upper = target * (1 + tol_ratio)
    return (interval >= lower) & (interval <= upper)


def format_ns(value: float) -> str:
    """Hiển thị ns dưới dạng dễ đọc."""
    if value >= 1_000_000_000:
        return f"{value/1e9:.3g} s"
    if value >= 1_000_000:
        return f"{value/1e6:.3g} ms"
    if value >= 1_000:
        return f"{value/1e3:.3g} µs"
    return f"{value:.3g} ns"


# =========================
# PLOT PER FILE
# =========================

def plot_file(path: str, targets: List[float], tol_ratio: float) -> None:
    """
    Vẽ 2 subplot (line + histogram) cho mỗi target của một file.
    """
    if not os.path.isfile(path):
        print(f"[WARN] File không tồn tại: {path}")
        return

    time, interval = load_file(path)
    filename = os.path.basename(path)

    n_targets = len(targets)
    fig = plt.figure(figsize=(14, 4.2 * n_targets))
    fig.suptitle(f"File: {filename}", fontsize=13, fontweight="bold", y=1.001)

    gs = gridspec.GridSpec(n_targets, 2, figure=fig, hspace=0.55, wspace=0.35)

    for i, target in enumerate(targets):
        mask = filter_by_target(interval, target, tol_ratio)
        t = time[mask]
        #t = time
        iv = interval[mask]
        #iv = interval

        ax_line = fig.add_subplot(gs[i, 0])
        ax_hist = fig.add_subplot(gs[i, 1])

        if len(iv) == 0:
            for ax in (ax_line, ax_hist):
                ax.set_title(f"Target {format_ns(target)} — no data", fontsize=9)
                ax.axis("off")
            continue

        mean = np.mean(iv)
        std  = np.std(iv)
        min_val = np.min(iv)
        max_val = np.max(iv)
        padding = (max_val - min_val) * 0.1
        error_pct = (mean - target) / target * 100

        stat_text = (
            f"n = {len(iv):,}\n"
            f"Mean  = {mean:,.2f} ns\n"
            f"Std   = {std:,.2f} ns\n"
            f"Min   = {min_val:,.2f} ns\n"
            f"Max   = {max_val:,.2f} ns\n"
            f"Error = {error_pct:+.3f}%"
        )

        # ── LEFT: Line plot ──────────────────────────────
        ax_line.plot(t, iv, linewidth=0.5, color="#378ADD", label="Interval")
        ax_line.set_ylim(0,400000)
        ax_line.axhline(target, linestyle="--", color="#444", linewidth=1.0, label="Target")
        ax_line.axhline(mean,   linestyle="--", color="#D85A30", linewidth=1.0, label="Mean")
        ax_line.set_title(f"Target = {format_ns(target)}", fontsize=9, fontweight="bold")
        ax_line.set_xlabel("Time (ns)", fontsize=8)
        ax_line.set_ylabel("Interval (ns)", fontsize=8)
        ax_line.tick_params(labelsize=7)
        ax_line.grid(True, linewidth=0.4, alpha=0.6)
        ax_line.legend(fontsize=7, loc="upper left")
        ax_line.text(
            0.98, 0.97, stat_text,
            transform=ax_line.transAxes,
            fontsize=7,
            verticalalignment="top",
            horizontalalignment="right",
            bbox=dict(boxstyle="round", facecolor="white", alpha=0.75),
            family="monospace",
        )

        # ── RIGHT: Histogram ─────────────────────────────
        ax_hist.hist(iv, bins=40, color="#B5D4F4", edgecolor="#378ADD", linewidth=0.4)
        ax_hist.axvline(target, linestyle="--", color="#444",    linewidth=1.0, label="Target")
        ax_hist.axvline(mean,   linestyle="--", color="#D85A30", linewidth=1.0, label="Mean")
        ax_hist.set_title(f"Distribution — {format_ns(target)}", fontsize=9, fontweight="bold")
        ax_hist.set_xlabel("Interval (ns)", fontsize=8)
        ax_hist.set_ylabel("Count", fontsize=8)
        ax_hist.tick_params(labelsize=7)
        ax_hist.grid(True, linewidth=0.4, alpha=0.6, axis="y")
        ax_hist.legend(fontsize=7, loc="upper right")

    plt.tight_layout()

    # Lưu ảnh cùng thư mục với file input
    out_dir  = os.path.dirname(os.path.abspath(path))
    out_name = os.path.splitext(filename)[0] + "_analysis.png"
    out_path = os.path.join(out_dir, out_name)
    fig.savefig(out_path, dpi=150, bbox_inches="tight")
    print(f"[OK] Saved → {out_path}")

    plt.show()


# =========================
# MAIN
# =========================

if __name__ == "__main__":
    # Cho phép truyền file qua command line:
    #   python interval_analysis.py data1.txt data2.txt data3.txt
    files = sys.argv[1:] if len(sys.argv) > 1 else FILE_PATHS

    if not files:
        print("Usage: python interval_analysis.py <file1.txt> [file2.txt ...]")
        sys.exit(1)

    for f in files:
        plot_file(f, targets=TARGETS, tol_ratio=TOL_RATIO)