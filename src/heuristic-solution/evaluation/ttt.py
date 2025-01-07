import pandas as pd
import matplotlib.pyplot as plt
import argparse

def generate_probability_distribution_plot(csv_path, output_path="probability_plot.png"):
    data = pd.read_csv(csv_path)

    plt.figure(figsize=(10, 6))

    for algorithm in data.columns:
        sorted_times = sorted(data[algorithm].dropna())
        n = len(sorted_times)

        probabilities = [(i - 0.5) / n for i in range(1, n + 1)]

        plt.plot(sorted_times, probabilities, label=algorithm)

    plt.xlabel("Time to Target (s)")
    plt.ylabel("Probability")
    # plt.title("Distribuição de Probabilidade (Time to Target)")
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.7)

    plt.savefig(output_path)
    plt.show()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        prog='TTT-Plotter',
        description='Plots a TTT Plot based on a csv file with CPU run times'
    )
    parser.add_argument('filename')
    parser.add_argument('output')

    args = parser.parse_args()
    generate_probability_distribution_plot(args.filename, args.output)
