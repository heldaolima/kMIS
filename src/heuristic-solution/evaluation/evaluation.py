import pandas as pd
import argparse

if __name__ == '__main__':
    BASE = '../../results/'
    parser = argparse.ArgumentParser(prog='Comparison between two result files',
                                     description='Reads the values of two .csv files and outputs the best one')

    parser.add_argument('-a', '--filea')
    parser.add_argument('-b', '--fileb')

    args = parser.parse_args()

    df1 = pd.read_csv(BASE+args.filea)#.sort_values(by='input')
    df2 = pd.read_csv(BASE+args.fileb)#.sort_values(by='input')

    df1_max_count = 0
    df2_max_count = 0
    equal_count = 0

    for index, (df1_row, df2_row) in enumerate(zip(df1.itertuples(), df2.itertuples())):
        if df1_row.input != df2_row.input:
            print(f"DIFERENTE: df1={df1_row.input} | df2={df2_row.input}")
            exit(1)

        df1_best = df1_row.best
        df2_best = df2_row.best

        max_val = max(df1_best, df2_best)

        print(df1_row.input, end="\t")
        print(f"df1={df1_best} | df2={df2_best}", end="\t")
        if df1_best == df2_best:
            print("[EQUAL]")
        elif df1_best == max_val:
            print("[df1]")
        elif df2_best == max_val:
            print("[df2]")
        if df1_best == df2_best:
            # print(f"Mesmo valor ({max_val})")
            equal_count += 1
        else:
            if df1_best == max_val:
                df1_max_count += 1
                # print(f"df1 ", end="")
            if df2_best == max_val:
                df2_max_count += 1
                # print(f"df2 ", end="")
            # print(f"({max_val})")

    print()
    print(f"{args.filea} teve o maior valor {df1_max_count} vezes")
    print(f"{args.fileb} teve o maior valor {df2_max_count} vezes")
    print(f"Os valores foram iguais {equal_count} vezes")
