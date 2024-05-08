#!/usr/bin/python3

import sys
import os
import hashlib
import base64

def main():
    if len(sys.argv) > 1:
        print("No arguments expected")
        return
    elif not os.path.exists("loghead.txt"):
        print("loghead.txt not found")
        return
    elif not os.path.exists("log.txt"):
        print("log.txt not found")
        return
    
    previous_line = ''
    failed = 0

    with open("log.txt", 'r') as log:
        for line in log:
            
            parts = line.split()

            if not previous_line:
                if parts[2] != "begin":
                    failed = 1
                    break
                previous_line = line
            else:
                if not parts[2] == base64.b64encode(hashlib.sha256(previous_line.encode()).digest()).decode():
                    failed = 1
                    break
                previous_line = line

    with open("loghead.txt", 'r') as head:
        if not head.read() == base64.b64encode(hashlib.sha256(previous_line.encode()).digest()).decode():
            failed = 1
    
    print("failed" if failed else "valid")

if __name__ == "__main__":
    main()