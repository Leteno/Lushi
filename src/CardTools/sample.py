
import sys

def main():
    for line in sys.stdin:
        line = line.replace('\n', '')
        print("I got a line: %s" % line)

if __name__ == '__main__':
    main()