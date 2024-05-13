import pandas as pd

if __name__ == "__main__":
    BASE = "../../results/"

    df_ils = pd.read_csv(BASE+"results_ils.csv").sort_values(by="input")
    df_grasp = pd.read_csv(BASE+"results_grasp.csv").sort_values(by="input")

    ils_max_count = 0
    grasp_max_count = 0
    equal_count = 0

    for index, (ils_row, grasp_row) in enumerate(zip(df_ils.itertuples(), df_grasp.itertuples())):
        if ils_row.input != grasp_row.input:
            print(f"DIFERENTE: ils={ils_row.input} | grasp={grasp_row.input}")
            exit(1)

        ils_best = ils_row.best
        grasp_best = int(grasp_row.best)

        max_val = max(ils_best, grasp_best)

        print(ils_row.input, end="\t")
        if ils_best == grasp_best :
            print(f"Mesmo valor ({max_val})")
            equal_count += 1
        else:
            if ils_best == max_val:
                ils_max_count += 1
                print(f"ILS ", end="")
            if grasp_best == max_val:
                grasp_max_count += 1
                print(f"GRASP ", end="")
            print(f"({max_val})")

    print()
    print(f"ILS teve o maior valor {ils_max_count} vezes")
    print(f"GRASP teve o maior valor {grasp_max_count} vezes")
    print(f"Os valores foram iguais {equal_count} vezes")



