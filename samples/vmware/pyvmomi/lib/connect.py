import atexit
import ssl

from pyVim.connect import Disconnect
from pyVim.connect import SmartConnect

def connect(host, user, password, port):
    """
    Connect to an ESX or vCenter host and return the service instance
    used to browse the inventory of managed objects.
    """
    context = ssl.SSLContext(ssl.PROTOCOL_TLSv1)
    context.verify_mode = ssl.CERT_NONE
    si = SmartConnect(host=host,
                      user=user,
                      pwd=password,
                      port=port,
                      sslContext=context)

    if si:
        atexit.register(Disconnect, si)

    return si
