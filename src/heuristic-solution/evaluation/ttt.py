import pandas as pd
import matplotlib.pyplot as plt
import argparse

def generate_probability_distribution_plot(csv_path, output_path="probability_plot.png"):
    data = pd.read_csv(csv_path)

    plt.figure(figsize=(8, 12))
    line_styles = ['-', '--', '-.', ':']
    colors = plt.cm.tab10.colors 
    print(colors)

    for idx, algorithm in enumerate(data.columns):
        sorted_times = sorted(data[algorithm].dropna())
        n = len(sorted_times)

        color = colors[idx % len(colors)]  # Cicla pelas cores
        line_style = line_styles[idx % len(line_styles)]  # Cicla pelos estilos

        probabilities = [(i - 0.5) / n for i in range(1, n + 1)]

        plt.plot(sorted_times,
                 probabilities,
                 label=algorithm,
                 color=color,
                 linestyle=line_style,
                 linewidth=2
                 )

    plt.xlabel("Time to Target (s)")
    plt.ylabel("Probability")
    plt.legend()

    plt.grid(True, linestyle="--", alpha=0.7)
    plt.ylim(0, 1.05)

    plt.savefig(output_path)
    plt.show()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        prog='TTT-Plotter',
        description='Plots a TTT Plot based on a csv file with CPU run times'
    )
    parser.add_argument('filename')

    args = parser.parse_args()

    output = args.filename.split('.')[0] + '.png'

    generate_probability_distribution_plot(args.filename, output)
