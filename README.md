# nmea-parse
Parses NMEA 0183 sentences (particularly from GPS receivers).

The output is a set of populated Google Protocol Buffer messages. The architecture is plugin-able to easily add or remove processing of specific NMEA sentences.

To-do's...
1. Build system upgrade to CMake so it will build easily on multiple architectures and double-check for dependencies
2. Abstract out common ASCII-text-parsing helpers
3. Perhaps parse the .proto and auto-generate code to parse the corresponding CSV line. Or have an XML definition auto-populate the corresponding .proto (not all info need be present in .proto). Then defining new message parsing is as easy as making a new XML file.
