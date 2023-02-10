prog=uagenda

# Normal usage

@test "Test par défaut" {
    run ./$prog test1
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "Everything is okay" ]
}