from sys import argv
import pandas as pd

if __name__ == "__main__":
    print(argv)

    if len(argv) != 3:
        print("USAGE: python countBest.py <df1.csv> <df2.csv>")

    df1 = pd.read_csv(argv[1])
    df2 = pd.read_csv(argv[2])

    count_df1 = (df1["best"] > df2["best"]).sum()
    count_df2 = (df2["best"] > df1["best"]).sum()
    count_eq = (df1["best"] == df2["best"]).sum()

    print(f"{argv[1]} ganhou {count_df1} vezes")
    print(f"{argv[2]} ganhou {count_df2} vezes")
    print(f"Obtiveram o mesmo valor {count_eq} vezes")

