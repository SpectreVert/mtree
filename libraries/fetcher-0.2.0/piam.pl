#!/usr/bin/env perl

#############################################################################
#                                                                           #
# Piam is 'Perl Importer Addon for Mtree'                                   #
# Piam is a simple way to import Deezer albums metadata to your computer    #
# and use it with mtree.                                                    #
#                                                                           #
# Run it with '-h', '--help' or '/?' for usage.                             #
#                                                                           #
#############################################################################

use warnings;
use strict;

use open ':encoding(UTF-8)';

package PiamParser;
use base 'HTML::Parser';
use JSON qw( decode_json );
use Getopt::Std;
use File::Path 'make_path';

# 1 = album
# 2 = artist

my $pflag = 0;
my $json_text = undef;
my $tmp_FILE = undef;

### Html extraction

sub start {
    my ($self, $tag, $attr, $attrseq, $origtext) = @_;

    unless ($tag =~ /^a$/) {
        return;
    }

    for my $i (@$attrseq) {
        if ($attr->{$i} =~ /^\/album\/(\d+)$/) {
            $pflag = 1;
            print ($tmp_FILE $1 . "/");
        } elsif ($attr->{$i} =~ /^\/artist\/(\d+)$/) {
            $pflag = 2;
            print ($tmp_FILE $1 . "/");
        }
    }
}

sub text {
    my ($self, $text) = @_;

    if ($pflag == 1) {
        print ($tmp_FILE $text . ":");
    } elsif ($pflag == 2) {
        print ($tmp_FILE $text . "\n");
    }  else {
        is_text_json($text);
    }

    $pflag = 0;
}

sub is_text_json {
    my $text = pop;

    if ($text =~ /^window\.__DZR_APP_STATE__ = (.*)$/) {
        $json_text = $1;
    }
}

### Fectcher core

sub main {
    my $p = new PiamParser;
    my $tmp_file = "tmp-" . rand();

    open ($tmp_FILE, '>', $tmp_file) or
        die "Could not open temp file";
    $p->parse_file("deezerpage.html");
    close $tmp_FILE;

    extract_infos($tmp_file, "/home/spectre/music/test");

    return 0;
}

sub extract_infos {
    my $old_file = shift;
    my $dest = shift;
    my $tmp_file = "tmp2-" . rand();

    open (my $old_FILE, '<', $old_file) or
        die "error: could not open temp file (reading)";

    open (my $tmp_FILE, '>', $tmp_file) or
        die "error: could not open temp file (writing)";

    while (<$old_FILE>) {
        if (not $json_text) {
            die "error: could not extract json information";
        } else {
            chomp;
            append_dates($tmp_FILE, $_);
        }
    }

    close $old_FILE;
    unlink $old_file;
    close $tmp_FILE;
    
    create_tree($tmp_file, $dest);
}

sub append_dates {
    my $tmp_FILE = shift;

    my $dec = decode_json($json_text);
    my @datas = @{$dec->{'TAB'}{'albums'}{'data'}};

    my @infos = split (':', shift);
    my @album = split ('/', $infos[0]);

    for my $data (@datas) {
        if ($data->{'ALB_TITLE'} eq $album[1]) {
            my @date = split ('-', $data->{'PHYSICAL_RELEASE_DATE'});
            ($infos[1], $album[1]) = correct_format($infos[1], $album[1]);

            print $tmp_FILE "$infos[1]:$album[0]/$date[0]-$album[1]\n";
        }
    }

}

sub create_tree {
    my $tmp_file = shift;
    my $dest = shift;

    open (my $tmp_FILE, '<', $tmp_file) or
        die "error: could not open temp file (reading)";

    chdir $dest;
    while (<$tmp_FILE>) {
        my @infos = split (':', $_);
        my @artist = split ('/', $infos[0]);
        my @album = split ('/', $infos[1]);

        chomp $album[1];
        print "$artist[1]/$album[1]/$album[0]\n";

        make_path("$artist[1]/$album[1]", {
            verbose => 1,
            chmod => 0755,
        });
    }

    close $tmp_FILE;
}

### Correcting format

sub correct_format {
    my ($artist, $album) = @_;

    $artist =~ tr/a-zA-Z0-9\_\-\//_/cs;
    $album =~ s/\'/-/g;
    $album =~ s/ - /-/g;
    $album =~ s/ /_/g;
    $album =~ s/\([^)]*\)//g;
    $album =~ s/[_-]?$//;

   return ($artist, $album);
}

exit &main;
