# AudioFX - Effects for instruments
# Created by Matheus Nogueira
#
# Simple amplifier
# Version 0.1
#
def options():
    # Low  [0-10]
    # Mid  [0-10]
    # High [0-10]
    return [
        {'name' : 'low', 'min' : 0, 'max' : 10, 'type' : 'int_scale'},
        {'name' : 'mid', 'min' : 0, 'max' : 10, 'type' : 'int_scale'},
        {'name' : 'high', 'min' : 0, 'max' : 10, 'type' : 'int_scale'},
    ]

def configure(options):
    return options

def execute(options):
    for dictionary in options:
        print(dictionary)