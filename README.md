# Sample Postgis PLY loader

Takes PLY files from IKG (X, Y, Z), where X, Y are DOUBLE while Z is FLOAT and pushes them to a postgis database points.

Does not create postgis geometry, this can be done afterwards using AddGeometryColumn and CREATE INDEX.

Note that this project is not a generic PLY to PGSQL converter, but easy to adopt to different PLY files by
modifying the ScanReader class in ikg_ply.hpp to fit your PLY datatypes and fields.

It uses tinyply (<https://github.com/ddiakopoulos/tinyply>), which has been copied / embedded into ikg_pc.hpp.

# Compile

This program needs client library support for postgres including c++ bindings.
