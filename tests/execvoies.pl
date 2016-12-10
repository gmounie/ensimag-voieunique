#!/usr/bin/perl -w
use v5.10;

open(my $fh, '../build/ensivoies; echo $? |');
while (my $ligne = <$fh>) {
	exit 0 if ($ligne =~ /The End/)
}
say "BUG: Exécution tronquée ? Pas d'affichage de 'The End'";
exit -1
