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
use base "HTML::Parser";
use JSON qw( decode_json );

# 1 = allbum
# 2 = artist

my $pflag = 0;
my $json_text = undef;
my $tmp_FILE = undef;

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
    } else {
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

sub main {
    my $p = new PiamParser;
    my $tmp_file = "tmp-" . rand();

    open ($tmp_FILE, '>', $tmp_file) or
        die "Could not open temp file";
    $p->parse_file("deezerpage.html");
    close $tmp_FILE;

    extract_infos($tmp_file);

    return 0;
}

sub extract_infos {
    my $old_file = shift;
    my $tmp_file = "tmp2-" . rand();

    open (my $old_FILE, '<', $old_file) or
        die "error: could not open temp file";

    open (my $tmp_FILE, '>', $tmp_file) or
        die "error: could not open temp file";

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

            print $tmp_FILE "$infos[1]:$album[0]/$date[0]$album[1]\n";
        }
    }
}

### Argument parsing

sub checkOpt {
        for my $arg (@ARGV) {
                if ($_[0] eq $arg) {
                        return 1;
                }
        }
        return 0;
}

sub getOpt {
        my @args = @_;

        for my $arg (@args) {
                if (checkOpt($arg) == 1) {
                        return 1;
                }
        }
        return 0;
}

sub nextOpt {
        my @checks = @_;

        for my $check (@checks) {
                my $count = 0;
                for my $arg (@ARGV) {
                        if ($check eq $arg && exists($ARGV[$count + 1])) {
                                return $ARGV[$count + 1];
                        }
                        $count++;
                }
        }
        return;
}

exit &main;
