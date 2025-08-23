import pandas as pd
import argparse
import os
import glob

outfile_path = 'partial_results.csv'

def main():
    parser = argparse.ArgumentParser(description="Process partial experiments results kept in CSV files in a directory")
    parser.add_argument("directory", type=str, help="Directory that contains complete partial experiment files, that end in '_detailed.csv'")

    args = parser.parse_args()

    dir = args.directory

    if not os.path.isdir(dir):
        print(f'Error: {dir} is not a directory')
        return

    search_pattern = os.path.join(dir, '*_detailed.csv')
    found_files = glob.glob(search_pattern)

    if not found_files:
        print(f'No file found in {dir}')

    results = []
    for file in found_files:
        print(f'Processing {file}')
        try:
            df = pd.read_csv(file)
            mean = df['obj'].mean()
            std_deviation = df['obj'].std()
            num_runs = len(df['obj'])

            exp_name = os.path.basename(file).replace('_detailed.csv', '')

            results.append({
                'experiment': exp_name,
                'mean': mean,
                'standard_deviation': std_deviation,
                'num_runs': num_runs,
            })

        except Exception as e:
            print(f'Error processing file {file}: {e}')

    if results:
        final_df = pd.DataFrame(results)
        final_df.to_csv(outfile_path, index=False)

        print(f'Results are saved in {outfile_path}')


if __name__ == '__main__':
    main()
