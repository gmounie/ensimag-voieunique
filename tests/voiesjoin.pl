#!/usr/bin/perl -w
use v5.10;


# in one second
open(my $fh, '/usr/bin/time -f "Temps ecoule: %E" ../build/ensivoies -d 500000  2>&1 | grep "Temps ecoule:" |');

my $ligne = <$fh>;
chomp($ligne);
my @mots = split ":", $ligne; # deux :, on ne teste que les secondes
if ($mots[1] != 0 or $mots[2] < 0.5 or  $mots[2] >= 1.0) {
	say "BUG: temps d'exécution du scénario 0 en $ligne s au lieu d'environ 0.5 secondes";
	exit -1;
}
close $fh;

# in three seconds
open($fh, '/usr/bin/time -f "Temps ecoule: %E" ../build/ensivoies -d 500000 -s 1 2>&1 | grep "Temps ecoule:" |');

$ligne = <$fh>;
chomp($ligne);
@mots = split ":", $ligne; # deux :, on ne teste que les secondes
if ($mots[1] != 0 or $mots[2] < 1.5 or  $mots[2] >= 2.0) {
	say "BUG: temps d'exécution du scénario 1 en $ligne s au lieu d'environ 1.5 seconde";
	exit -1;
}
close $fh;

exit 0;
