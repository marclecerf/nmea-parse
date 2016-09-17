# nmea-parse
Parses NMEA 0183 sentences (particularly from GPS receivers).

The output is a set of populated Google Protocol Buffer messages. The architecture is plugin-able to easily add or remove processing of specific NMEA sentences.
