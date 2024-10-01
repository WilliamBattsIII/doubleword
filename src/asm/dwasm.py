import sys
import argparse

parser = argparse.ArgumentParser("dwasm")
parser.add_argument("source", help="The file containing the source code you want to assemble.", type=str)
args = parser.parse_args()

srcfile = open(args.source, "r")

def parseline(line):
    # splits = line.split(" ")
    # for i in range(len(splits)):
    #   pass
    pass # do this later