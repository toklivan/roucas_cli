# roucas_cli - PLAN (v1)

## Objectif v1
Implemeter une CLI en C pour gerer un stock de produits via un fichier CSV.

## Milestones

### M0 - Repo ready
- [x] SPEC.md push

### M1 - Project skeleton
- [x] README.md minimal
- [x] .gitignore
- [x] folders: src/, include/, data/

### M2 - Data model
- [x] define `t_product`
- [x] choose in-memory container (linked list)
- [x] define CSV line format

### M3 - CSV I/O
- [x] load CSV into memory
- [ ] save memory to CSV (rewrite file)

### M4 - Commands
- [ ] `list`
- [ ] `add`
- [ ] `sell`
- [ ] `restock`
- [ ] `low`

### M5 - Errors & UX
- [ ] argument parsing + `--help`
- [ ] clear error messages + non-zero exit codes

### M6 - Polish
- [ ] examples in README
- [ ] sample `data/stock.csv`