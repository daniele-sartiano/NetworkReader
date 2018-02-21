#!/usr/bin/env python3

import sys
import os

def main():
    exclude = sys.argv[1]

    for line in sys.stdin:
        line = line.strip()
        subpath = line.replace(exclude, '')
        ip = os.path.dirname(subpath).replace('/', '.')
        if not ip:
            ip = '*'
        print('\t'.join((line, os.path.splitext(os.path.basename(subpath))[0], ip)))

if __name__ == '__main__':
    main()
