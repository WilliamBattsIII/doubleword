import argparse

parser = argparse.ArgumentParser("dwasm")
parser.add_argument("source", help="The file containing the source code you want to assemble.", type=str)
args = parser.parse_args()

srcfile = open(args.source, "r")

# 1A 00 00 00 8E 80 00 40 8E 80 00 58 2C 00 00 20

def parseline(line):
    splits = line.split(" ")
    for i in range(len(splits)):
        if(splits[i] is ".org"):
            baseaddr = int(splits[i + 1], 16)