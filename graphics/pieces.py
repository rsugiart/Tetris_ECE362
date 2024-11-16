#!/usr/bin/env python3

block_size = 20
piece_width = 4 * block_size
piece_height = 4 * block_size
name = "tetris_pieces"

tetris_pieces = {
    "O": [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [1, 1, 0, 0],
        [1, 1, 0, 0]
    ],
    "I": [
        [0, 0, 0, 0],
        [1, 1, 1, 1],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
}


def generate_piece_pixel_data(piece):
    """Generates pixel data for a single piece."""
    width = piece_width
    height = piece_height

    arr = [[0x0000 for _ in range(height)] for _ in range(width)]
    
    for grid_y in range(4):
        for grid_x in range(4):
            if piece[grid_y][grid_x] == 1:
                # Fill the corresponding block in the 20x20 area
                for x in range(grid_x * block_size, (grid_x + 1) * block_size):
                    for y in range(grid_y * block_size, (grid_y + 1) * block_size):
                        arr[x][y] = 0xffff 

    return arr

def write_c_file(pieces):
    """Writes the C file containing pixel data for all Tetris pieces."""
    with open('./tetris_pieces.c', 'w') as out:
        # Header
        out.write("const struct {\n")
        out.write("  unsigned int width;\n")
        out.write("  unsigned int height;\n")
        out.write("  unsigned int bytes_per_pixel;\n")
        out.write("  unsigned char pixel_data[80 * 80 * 2];\n")
        out.write("} tetris_pieces[] = {\n")

        for piece_name, piece in pieces.items():
            width = piece_width
            height = piece_height
            arr = generate_piece_pixel_data(piece)

            out.write("  {\n")
            out.write(f"    {width}, {height}, 2,\n")

            # Write pixel data
            #out.write("    \"\n")
            for y in range(height):
                out.write("\"")
                for x in range(width):
                    out.write(f"\\{arr[x][y] & 0xff:03o}\\{arr[x][y] >> 8:03o}")
                out.write("\"\n")
            #out.write("    \"\n")
            out.write("},\n")

        out.write("};\n")

# Generate the C file
write_c_file(tetris_pieces)
