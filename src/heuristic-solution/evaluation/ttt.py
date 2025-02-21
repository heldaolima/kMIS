import pandas as pd
import matplotlib.pyplot as plt
import argparse
import os

def generate_probability_distribution_plot(csv_path, output_path):
    data = pd.read_csv(csv_path)
    plt.figure(figsize=(12, 12))
    line_styles = ['-', '--', '-.', ':']
    colors = plt.cm.Set1.colors

    for idx, algorithm in enumerate(data.columns):
        if algorithm == "ILS-3":
            continue

        sorted_times = sorted(data[algorithm].dropna() * 1000)  
        n = len(sorted_times)

        color = colors[idx % len(colors)]  
        line_style = line_styles[idx % len(line_styles)]  

        probabilities = [(i - 0.5) / n for i in range(1, n + 1)]

        plt.plot(sorted_times,
                 probabilities,
                 label=algorithm,
                 color=color,
                 linestyle=line_style,
                 linewidth=2
                 )

    plt.xlabel("Time to Target (ms)", fontsize=30)
    plt.ylabel("Probability", fontsize=30)
    plt.legend(fontsize=32)

    plt.tick_params(axis='both', which='major', labelsize=25)
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.ylim(0, 1.05)

    plt.savefig(output_path)
    plt.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        prog='TTT-Plotter',
        description='Plots a TTT Plot for each CSV file in a directory'
    )
    parser.add_argument('directory', help='Path to the directory containing CSV files')

    args = parser.parse_args()

    csv_files = [os.path.join(args.directory, f) for f in os.listdir(args.directory) if f.endswith('.csv')]

    if not csv_files:
        print("No CSV files found in the directory.")
    else:
        for csv_file in csv_files:
            output = os.path.join(args.directory, os.path.splitext(os.path.basename(csv_file))[0] + 'no_reactive_plot.png')
            generate_probability_distribution_plot(csv_file, output)
