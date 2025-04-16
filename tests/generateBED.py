import random
import os

def main():
    generate()

def generate():
    sizes = {"1K": 1000, "10K": 10000, "100K": 100000,
            "1M": 1000000, "2M": 2000000, "3M": 3000000,
            "4M": 4000000, "5M": 5000000, "6M": 6000000,
            "7M": 7000000, "8M": 8000000, "9M": 9000000,
            "10M": 10000000}

    # create folder unsorted
    os.makedirs("bedfiles", exist_ok=True)

    # chromosomes
    chrs = [f'chr{i}' for i in range(1, 23)] + ['chrX', 'chrY']
    for entry in sizes:
        print(entry)
        fh = open(f"bedfiles/bed_{entry}.bed", 'w')
        entries = sizes[entry]
        for line in range(0, entries):
            chr = random.choice(chrs)
            start = random.randint(1, 100000000)
            end = start + random.randint(100, 10000)

            fh.write(f"{chr}\t{start}\t{end}\n")
        fh.close()

        # sort bed file
        os.system(f"sort -k1,1 -k2,2n bedfiles/bed_{entry}.bed > bedfiles/bed_{entry}_sorted.bed")


main()
