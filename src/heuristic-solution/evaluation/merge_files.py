import csv

def merge_files_to_csv(file1, file2, output_csv):
    with open(file1, 'r') as f1:
        numbers1 = f1.read().splitlines()

    with open(file2, 'r') as f2:
        numbers2 = f2.read().splitlines()

    max_length = max(len(numbers1), len(numbers2))
    numbers1.extend([''] * (max_length - len(numbers1)))
    numbers2.extend([''] * (max_length - len(numbers2)))

    with open(output_csv, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['ILS-1', 'ILS-2']) 
        csv_writer.writerows(zip(numbers1, numbers2))

import argparse
parser = argparse.ArgumentParser(
    prog='Files merger .csv'
)

parser.add_argument('file1_path')
parser.add_argument('file2_path')
parser.add_argument('output')

args = parser.parse_args()

file1_path = args.file1_path
file2_path = args.file2_path
output_csv_path = args.output + '.csv'

merge_files_to_csv(file1_path, file2_path, output_csv_path)
print(f"Arquivo CSV '{output_csv_path}' criado com sucesso.")

