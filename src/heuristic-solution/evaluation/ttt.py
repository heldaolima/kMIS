import pandas as pd
import matplotlib.pyplot as plt
import argparse
import os


def generate_ttt_plots(csv_path, output_path):
    os.makedirs(output_path, exist_ok=True)

    data = pd.read_csv(csv_path)

    unique_instances = data['instance'].unique()
    unique_algorithm = data['algorithm'].unique()

    line_styles = ['-', '--', '-.', ':']
    colors = plt.cm.Set1.colors

    for instance in unique_instances:
        instance_data = data[data['instance'] == instance]
        plt.figure(figsize=(12, 12))

        for idx, algorithm in enumerate(unique_algorithm):
            # if algorithm == 'ILS-3':
            #     continue
            algorithm_data = instance_data[instance_data['algorithm'] == algorithm]

            sorted_times = sorted(algorithm_data['time'].dropna())
            n = len(sorted_times)

            if n > 0:
                probabilities = [(i - 0.5) / n for i in range(1, n + 1)]

                color = colors[idx % len(colors)]
                line_style = line_styles[idx % len(line_styles)]

                plt.plot(sorted_times,
                         probabilities,
                         label=algorithm,
                         color=color,
                         linestyle=line_style,
                         linewidth=4)

        plt.xlabel("Time to Target (s)", fontsize=30)
        plt.ylabel("Probability", fontsize=30)
        # plt.title(f'TTT Plot for Instance: {instance}', fontsize=32)
        plt.legend(fontsize=28)
        plt.tick_params(axis='both', which='major', labelsize=25)
        plt.grid(True, linestyle="--", alpha=0.7)
        plt.ylim(0, 1.05)

        # Save the plot with the instance name in the filename
        output = os.path.join(output_path, f'{instance}_ttt_plot.png')
        print('output path:', output)
        plt.savefig(output, format='png')
        plt.close()
        print(f'Generated plot for instance: {instance}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        prog='TTT-Plotter',
        description='Plots a TTT Plot for each instance in a single CSV file'
    )
    parser.add_argument(
        'csv_file', help='Path to the input CSV file'
    )
    parser.add_argument(
        '--output_dir', default='./ttt_results', help='Directory to save the output plots'
    )

    args = parser.parse_args()

    if os.path.exists(args.csv_file):
        generate_ttt_plots(args.csv_file, args.output_dir)
    else:
        print(f'Error: The file {args.csv_file} was not found')
