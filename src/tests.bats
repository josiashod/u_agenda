prog=uagenda

# Normal usage

@test "Test par défaut" {
    run ./$prog test1
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Everything is okay" ]
}

@test "Création et modification d'une personne" {
    run ./$prog test_creation_modification
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Josh PRICE" ]
    [ "${lines[1]}" = "John DOH" ]
}

@test "Mise à jour email" {
    run ./$prog test_update_mail
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "test@gmail.com" ]
    [ "${lines[1]}" = "john.doe@gmail.com" ]
}

@test "Mise à jour numero" {
    run ./$prog test_update_numero
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "0606060606" ]
    [ "${lines[1]}" = "0707070707" ]
}

@test "Affiche personne" {
    run ./$prog test_affiche_personne
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "{DOH, John, john.doe@gmail.com, 0606060606}" ]
}

@test "Création d'une personne avec mauvais numero" {
    run ./$prog test_mauvais_numero
    [ "$status" -eq 2 ]
}

@test "Création d'une personne avec mauvais email" {
    run ./$prog test_mauvais_email
    [ "$status" -eq 2 ]
}

@test "Modification du mail avec un mauvais" {
    run ./$prog test_update_avec_mauvais_email
    [ "$status" -eq 2 ]
}

@test "Modification du numero avec un mauvais" {
    run ./$prog test_update_avec_mauvais_numero
    [ "$status" -eq 2 ]
}