#Test script for btasm

use Term::ANSIColor;

my $prog = "./lexer";


#----------------
#Run the tests
#----------------
test("Basic parse", "", "tests");
test("Phase 1 parse","-1", "tests");



#Run a test on folder $dirname.  Title with header $header, and run command $command.
sub test {
    
    my ($header, $ops, $dirname,) = @_;
    

    #print a nice header
    print color "cyan";
    print "\n\n\n------------------------------------\n";
    print $header;
    print "\n------------------------------------\n\n";
    print color "reset";


    #for each file in tests dir...
    opendir(DIR, $dirname) or die "can't opendir $dirname: $!";
    while (defined($file = readdir(DIR))) {
        
        if (!($file =~ m/.+\.txt/) || ($file =~ m/.+\.b/)) {
            next;
        }


        #Print the path:
        my $path = $dirname . "/" . $file;
        print $path .": ";
     
        my $call = $prog . " " . $ops . " " . $path . " >& /dev/null";

        if (system($call) != 0) {
            print color "red bold";
            print "FAILED";
        } else {
            print color "green bold";
            print "OK";    
        }
        
        print color "reset"; print "\n";
    }

    closedir(DIR);

}
