#!/usr/bin/perl

# Inputs a graph in Dimacs format on STDIN
# Outputs a frequency histogram of the vertex degrees

# written by Charles Phillips
# Deptartment of Electrical Engineering and Computer Science
# University of Tennessee

my $line = <STDIN>;
chomp $line;
my @fields = split(/\t/, $line);

$numvertices = $fields[0];
$numedges = $fields[1];
$count = 0;
$maxdegree = 0;

while (my $line = <STDIN>)
{
	chomp $line;
	my @fields = split(/\t/, $line);

	if (exists $vertices{$fields[0]}) {
		$vertices{$fields[0]} = $vertices{$fields[0]} + 1;
		if ($vertices{$fields[0]} > $maxdegree) {
			$maxdegree = $vertices{$fields[0]};
		}
	}
	else {
		$vertices{$fields[0]} = 1;
	}

	if (exists $vertices{$fields[1]}) {
		$vertices{$fields[1]} = $vertices{$fields[1]} + 1;
		if ($vertices{$fields[1]} > $maxdegree) {
			$maxdegree = $vertices{$fields[1]};
		}
	}
	else {
		$vertices{$fields[1]} = 1;
	}

	$count++;
}

if ($count != $numedges) 
{
	die "Error: Number of edges does not match declared value.\n";
}

for ($i=0; $i<=$maxdegree; $i++)
{
	$freqcount[$i] = 0;
}

for my $key ( keys %vertices ) 
{
	$freqcount[$vertices{$key}]++;
}

for ($i=0; $i<=$maxdegree; $i++)
{
	print "$i\t$freqcount[$i]\n";
}

