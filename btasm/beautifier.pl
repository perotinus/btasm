###########################
#User options
my $tab = '    ';    #A tab - change to your desired number of spaces
my $spaced = 1;      #Blank addition (0=none, 1=some, 2=lots)
my $lineSqueeze = 1; #Squeeze commands and arguments together    
###########################


my $numtabs = 0;     #Number of tabs to add to front
my $taboffset = 0;   #Number of tabs to offset 

if ($#ARGV != 0) {
    print "beautifier.pl <bsm file to beautify>\n";
    exit;
}

open FILE, "<", $ARGV[0] or die $!;

while (<FILE>) {

    $taboffset = 0;
    my $newline = '';

    
    if ($_ =~ m/^\s+$/) {
        next;
    }

    $_ =~ s/^\s+//;
    $_ =~ s/\s+\n$/\n/;

    if ($lineSqueeze == 1) {
        $_ =~ s/\b\s+\b/ /g;
    }

    #Check for an indent construct
    if ($_ =~ m/(\bIF|\bFUNCTION|\bEVENT)/) {
        $newline = "\n";
        $numtabs++;
        $taboffset = 1;
    }

    #Check for an unindent construct
    if ($_ =~ m/(END_IF|END_FUNCTION|END_EVENT)/) {
        $numtabs = $numtabs - 1;
        $newline = "\n";
    }

    if ($_ =~ m/(END_FUNCTION|END_STATE)/) {
        $newline = $newline . "\n";
    }

    if ($_ =~ m/(END_STATE|\bSTATE)/) {
        $newline = $newline . "\n";
    }
    if ($_ =~ m/ELSE/) {
        $taboffset = 1;
    }

    if ($spaced == 0) {
        print $tab x ($numtabs - $taboffset) . $_;
    } elsif ($spaced == 1) {
        print $tab x ($numtabs - $taboffset) . $_ . $newline;
    } elsif ($spaced == 2) {
        print $newline . $tab x ($numtabs - $taboffset) . $_ . $newline;
    }

}

