#!/usr/bin/env python

"""
Connect to an ESX / vCenter host
"""

from lib.args import get_args
from lib.connect import connect
from lib.inventory import get_datacenter

def main():
    global datacenter

    args = get_args()

    si = connect(args.host, args.user, args.password, int(args.port))
    if not si:
        print("Error: Could not connect to the specified host using specified "
              "username and password")
        return -1

    datacenter = get_datacenter(si)
    print('datacenter: %s' % datacenter.name)
    return 0

# Start program
if __name__ == "__main__":
    main()
