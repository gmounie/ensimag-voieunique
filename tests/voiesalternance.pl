#!/usr/bin/perl -w
use v5.10;


# two sets interlaced: two passage
open(my $fh, './ensivoies -s 3 | grep "entree, sens [01]" | sed "s/.*entree, \(sens .\).*/\1/" | uniq | wc -l |');

my $ligne = <$fh>;
chomp($ligne);
if ($ligne != 2) {
	say "BUG: entrelacement du scénario 3 en $ligne groupes au lieu de 2";
	exit -1;
}
close $fh;

# in three seconds
open($fh, './ensivoies -s 5 | grep "entree, sens [01]" | sed "s/.*entree, \(sens .\).*/\1/" | uniq | wc -l |');

$ligne = <$fh>;
chomp($ligne);
if ($ligne != 8) {
	say "BUG: entrelacement du scénario 5 en $ligne groupes au lieu de 8";
	exit -1;
}
close $fh;

exit 0;
