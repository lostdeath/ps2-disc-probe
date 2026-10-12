#!/usr/bin/env python3
"""Create an opaque 512x512 RGB PNG for a minimal OpenOrbis app."""
import pathlib
import struct
import sys
import zlib

def chunk(kind: bytes, payload: bytes) -> bytes:
    return struct.pack(">I", len(payload)) + kind + payload + struct.pack(">I", zlib.crc32(kind + payload) & 0xFFFFFFFF)

def main() -> None:
    destination = pathlib.Path(sys.argv[1])
    destination.parent.mkdir(parents=True, exist_ok=True)
    width = height = 512
    rows = []
    for y in range(height):
        row = bytearray(b"\x00")
        for x in range(width):
            # 24-bit opaque gradient; intentionally no alpha channel.
            row.extend((20 + (x * 40 // 511), 50 + (y * 65 // 511), 120))
        rows.append(bytes(row))
    png = (b"\x89PNG\r\n\x1a\n"
           + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
           + chunk(b"IDAT", zlib.compress(b"".join(rows), 9))
           + chunk(b"IEND", b""))
    destination.write_bytes(png)
    print("wrote RGB 24-bit icon:", destination, len(png), "bytes")

if __name__ == "__main__":
    main()
