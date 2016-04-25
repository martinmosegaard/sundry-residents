def get_datacenter(si):
    """
    Get a datacenter from the service instance of an ESX or vCenter host.
    """
    content = si.RetrieveContent()
    for child in content.rootFolder.childEntity:
        if hasattr(child, 'vmFolder'):
            return child
    return None
