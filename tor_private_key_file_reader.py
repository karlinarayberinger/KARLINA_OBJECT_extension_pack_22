#########################################################################################
# file: tor_private_key_file_reader.py
# type: Python
# date: 05_OCTOBER_2024
# author: karbytes
# license: PUBLIC_DOMAIN 
#########################################################################################

import sys  # for printing to (and possibly generating) the output file
from cryptography.hazmat.primitives.asymmetric import ed25519
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization  # Import missing module

# Read the binary file containing the private key
key_file_path = 'hs_ed25519_secret_key'  # Ensure the correct path is used

try:
    with open(key_file_path, 'rb') as key_file:
        private_key_data = key_file.read()

    # Open the file for writing (and generate that file if it does not exist)
    with open("tor_private_key_file_reader_OUTPUT.txt", "w") as output_file:
        
        # Print the entire file in hex format to inspect its structure
        print(f"Private key file content (hex): {private_key_data.hex()}")
        print(f"Private key file length: {len(private_key_data)} bytes")

        # Write to the output file
        output_file.write(f"Private key file content (hex): {private_key_data.hex()}\n")
        output_file.write(f"Private key file length: {len(private_key_data)} bytes\n")

        # Assuming the first 32 bytes contain the actual private key
        if len(private_key_data) >= 32:
            actual_private_key = private_key_data[:32]  # Extract the first 32 bytes
            
            # Load the private key
            private_key = ed25519.Ed25519PrivateKey.from_private_bytes(actual_private_key)
            
            # Get the raw private bytes
            raw_private_bytes = private_key.private_bytes(
                encoding=serialization.Encoding.Raw,
                format=serialization.PrivateFormat.Raw,
                encryption_algorithm=serialization.NoEncryption()
            )
            
            # Print the raw private key in hexadecimal format
            print(f"Extracted Private key (hex): {raw_private_bytes.hex()}")
            output_file.write(f"Extracted Private key (hex): {raw_private_bytes.hex()}\n")
        else:
            print("Error: The file does not contain enough data for a 32-byte Ed25519 private key.")
            output_file.write("Error: The file does not contain enough data for a 32-byte Ed25519 private key.\n")

except FileNotFoundError:
    print(f"Error: The file {key_file_path} was not found.")
except Exception as e:
    print(f"An error occurred: {e}")
