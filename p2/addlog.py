#!/usr/bin/python3

import os
import sys
from datetime import datetime
import hashlib
import base64

def main():
    if len(sys.argv) != 2:
        print("Usage: ./addlog.py [log string]")
        return

    input_string = sys.argv[1].replace('\n', ' ')

    if os.path.exists("log.txt"):

        if not os.path.exists("loghead.txt"):
            print("Head file missing")
            return
        
        log = open("log.txt", 'a')
        with open("loghead.txt", 'r') as head:
            hash_string = head.read()
    else:

        log = open("log.txt", 'w')
        hash_string = "begin"
    
    date = datetime.now().isoformat()
    log_string = date + " - " + hash_string + " " + input_string + "\n"
    log.write(log_string)

    hash_string = base64.b64encode(hashlib.sha256(log_string.encode()).digest()).decode()
    with open("loghead.txt", 'w') as head:
        head.write(hash_string)

    log.close(), head.close()

if __name__ == "__main__":
    main()