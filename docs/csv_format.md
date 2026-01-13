# CSV format - roucas_cli (v1)

## Header
The first line must be:
`id,name,category,buy_price,sell_price,stock,low_threshold`

This header is ignored by the program.

## Separator
Fields are separeted by a comma `,`.

## Text fields restrictions
- `id`, `name`, `category` must not contain commas.
- Leading/trailing spaces are trimmed.

## Numeric fields
- `buy_price` and `sell_price` are parsed as `double` (decimal allowed).
- `stock` and `low_threshold` are parsed as `int`.

Invalid numbers (e.g. `12abc`) are rejected.

## Validation rules
- Each data line must have exactly 7 columns.
- `id` must be unique.
- `stock` must be >= 0.
- `low_threshold` must be >= 0.
- If a line is invalid, the program exits with a non-zero status and prints an error message.