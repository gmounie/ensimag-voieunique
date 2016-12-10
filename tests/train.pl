#!/usr/bin/perl -w
use v5.10;

open(my $fh, 'strace -f ../build/ensivoies -s 0 2>&1 | grep "CLONE_THREAD" | wc -l |');

my $ligne = <$fh>;
chomp($ligne);
if ($ligne == 1) {
	exit 0;
}
say "BUG: $ligne threads créés au lieu de 5";
exit -1;
