import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog="Calculate time to run a experiment")
    parser.add_argument("instances")

    args = parser.parse_args()
    instances_file = args.instances

    instances = []
    with open(instances_file, 'r') as f:
        instances = f.read().splitlines()

    count = 0
    for instance in instances:
        with open(instance, 'r') as f:
            # will run 10 times, therefore no need to divide by 10
            count += int(f.readline().split(' ')[3].rstrip())

    seconds = count*5
    print(
        f"The experiment will take {seconds} seconds to run, {seconds/60} minutes, {seconds/60/60} hours")
