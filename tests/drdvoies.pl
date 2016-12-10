#!/usr/bin/perl -w
use v5.10;

open(my $fh, 'valgrind --tool=drd  --error-exitcode=2 -q ../build/ensivoies -s 4 2>&1; echo "Returned code:" $? |');
while (my $ligne = <$fh>) {
	chomp($ligne);
	if ($ligne =~ /Returned code: 0/) {
		exit 0;
	}
}
close $fh;
exit -1;

