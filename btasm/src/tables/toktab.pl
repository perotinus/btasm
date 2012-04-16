#!/usr/bin/env perl

open (FILE, 'src/y.tab.h');

my $state = 0;
my %hash = ();
my $n = 0;

while (<FILE>) {
    
    chomp;
    
    my $string = $_;

    #Not yet in enum
    if ($state == 0) {
        if ($string =~ m/enum/) {
            $state = 1;
            next;
        }
    } elsif ($state == 1) {
        if ($string =~ m/};\s*$/) { #End of ENUM
            $state = 0;
            next;
        }
        
        $string =~ /([A-Z0-9_]+)\s+=\s+([0-9]+)/;

        $hash{$2} = $1;

        #print $n, "--", $2;
        #$n = $n+1;

        #print $1,"=", $2,"\n";
    }


}
 
open (OFILE, ">>src/tables/toktab.h");

foreach my $key (sort keys %hash) {
    print OFILE "\ttoktab[" , $key , "] = \"", $hash{$key} , "\";\n"
}

print OFILE "}\n #endif"
        
                
        
        
