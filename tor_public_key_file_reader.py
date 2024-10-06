#########################################################################################
# file: tor_public_key_file_reader.py
# type: Python
# date: 05_OCTOBER_2024
# author: karbytes
# license: PUBLIC_DOMAIN 
#########################################################################################

# Adding the missing import for serialization
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ed25519

# Read the binary file containing the public key
key_file_path = 'hs_ed25519_public_key'  # Ensure the correct path is used
output_file_path_public = 'tor_public_key_file_reader_OUTPUT.txt'  # Output file path

# Re-run the program with the missing imports fixed
try:
    with open(key_file_path, 'rb') as key_file:
        public_key_data = key_file.read()

    # Open the file for writing (and generate that file if it does not exist)
    with open(output_file_path_public, "w") as output_file:
        
        # Print the entire file in hex format to inspect its structure
        print(f"Public key file content (hex): {public_key_data.hex()}")
        print(f"Public key file length: {len(public_key_data)} bytes")

        # Write to the output file
        output_file.write(f"Public key file content (hex): {public_key_data.hex()}\n")
        output_file.write(f"Public key file length: {len(public_key_data)} bytes\n")

        # Since the file length is 64 bytes, let's assume the second half contains the 32-byte public key
        if len(public_key_data) == 64:
            actual_public_key = public_key_data[32:]  # Extract the last 32 bytes
            
            # Load the public key
            public_key = ed25519.Ed25519PublicKey.from_public_bytes(actual_public_key)
            
            # Get the raw public bytes (this step is technically redundant since we already have the public key data)
            raw_public_bytes = public_key.public_bytes(
                encoding=serialization.Encoding.Raw,
                format=serialization.PublicFormat.Raw
            )
            
            # Print the raw public key in hexadecimal format
            print(f"Extracted Public key (hex): {raw_public_bytes.hex()}")
            output_file.write(f"Extracted Public key (hex): {raw_public_bytes.hex()}\n")
        else:
            print("Error: The file does not contain a valid 32-byte Ed25519 public key.")
            output_file.write("Error: The file does not contain a valid 32-byte Ed25519 public key.\n")

except FileNotFoundError:
    print(f"Error: The file {key_file_path} was not found.")
except Exception as e:
    print(f"An error occurred: {e}")

# Return the output file path
output_file_path_public
