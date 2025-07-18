import os
import random

BASE = '/home/helder/coders/kMIS/src/instances/'

dirs = ['type1', 'type2', 'type3']
num_files = 27
output = 'selected_instances.txt'

if __name__ == '__main__':
    all_files = []
    for dir in dirs:
        dir_path = os.path.join(BASE, dir)
        if not os.path.isdir(dir_path):
            print('Dir not found:', dir_path)
            continue

        for entry in os.listdir(dir_path):
            all_files.append(os.path.join(dir_path, entry))

        selected_files = random.sample(all_files, num_files)

        with open(output, 'w') as f:
            for file in selected_files:
                f.write(file+'\n')
