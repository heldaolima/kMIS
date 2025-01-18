import csv
import argparse

def add_column_to_csv(csv_file_path, other_file_path, output_csv_path, new_column_name):
    """
    Adiciona uma nova coluna ao arquivo CSV com o conteúdo do outro arquivo.
    
    :param csv_file_path: Caminho para o arquivo .csv original.
    :param other_file_path: Caminho para o outro arquivo (mesmo número de linhas).
    :param output_csv_path: Caminho para salvar o arquivo .csv de saída.
    :param new_column_name: Nome da nova coluna a ser adicionada.
    """
    # Lê o conteúdo do outro arquivo
    with open(other_file_path, 'r', encoding='utf-8') as other_file:
        other_lines = other_file.read().splitlines()
    
    # Lê o conteúdo do arquivo CSV original
    with open(csv_file_path, 'r', encoding='utf-8') as csv_file:
        reader = csv.reader(csv_file)
        csv_rows = list(reader)
    
    # Verifica se o número de linhas é compatível
    if len(other_lines) != len(csv_rows) - 1:  # Subtrai 1 para considerar o cabeçalho do CSV
        raise ValueError("O número de linhas no outro arquivo deve corresponder ao número de linhas de dados no arquivo CSV.")
    
    # Adiciona a nova coluna
    csv_rows[0].append(new_column_name)  # Adiciona o nome da nova coluna ao cabeçalho
    for i, line in enumerate(other_lines, start=1):  # Começa após o cabeçalho
        csv_rows[i].append(line)
    
    # Escreve o novo arquivo CSV
    with open(output_csv_path, 'w', encoding='utf-8', newline='') as output_file:
        writer = csv.writer(output_file)
        writer.writerows(csv_rows)


arg_parser = argparse.ArgumentParser(description='Adiciona uma nova coluna ao arquivo CSV com o conteúdo do outro arquivo.')
arg_parser.add_argument('csv_file', help='Caminho para o arquivo .csv original.')
arg_parser.add_argument('other_file', help='Caminho para o outro arquivo (mesmo número de linhas).')
arg_parser.add_argument('column_name', help='Nome da nova coluna a ser adicionada.')

args = arg_parser.parse_args()

# Exemplo de uso
csv_file = args.csv_file
other_file = args.other_file
output_file = 'output.csv'
new_column = args.column_name

add_column_to_csv(csv_file, other_file, output_file, new_column)

