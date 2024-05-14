import pandas as pd

if __name__ == "__main__":
    BASE = "../../results/"

    df_ils = pd.read_csv(BASE+"results_ils.csv").sort_values(by="input")
    df_vns = pd.read_csv(BASE+"results_vns.csv").sort_values(by="input")

    ils_max_count = 0
    vns_max_count = 0
    equal_count = 0

    for index, (ils_row, vns_row) in enumerate(zip(df_ils.itertuples(), df_vns.itertuples())):
        if ils_row.input != vns_row.input:
            print(f"DIFERENTE: ils={ils_row.input} | vns={vns_row.input}")
            exit(1)

        ils_best = ils_row.best
        vns_best = vns_row.best

        max_val = max(ils_best, vns_best)


        print(ils_row.input, end="\t")
        print(f"ILS={ils_best} | VNS={vns_best}", end="\t")
        if ils_best == vns_best:
            print("[EQUAL]")
        elif ils_best == max_val:
            print("[ILS]")
        elif vns_best == max_val:
            print("[VNS]")
        if ils_best == vns_best:
            # print(f"Mesmo valor ({max_val})")
            equal_count += 1
        else:
            if ils_best == max_val:
                ils_max_count += 1
                # print(f"ILS ", end="")
            if vns_best == max_val:
                vns_max_count += 1
                # print(f"VNS ", end="")
            # print(f"({max_val})")

    print()
    print(f"ILS teve o maior valor {ils_max_count} vezes")
    print(f"VNS teve o maior valor {vns_max_count} vezes")
    print(f"Os valores foram iguais {equal_count} vezes")



