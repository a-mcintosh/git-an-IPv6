git-an-IPv6
================================
Copyright (c) 2022 Aubrey McIntosh, PhD


###8MC2kMMxmjWCEPC81yjYy2bhCQeeU5RTa8
* [Markdown Tutorial](https://agea.github.io/tutorial.md "Markdown Tutorial")
* [github repository](https://github.com/a-mcintosh/git-an-IPv6.git "github repository")
* [Unique Local IPv6 Unicast Addresses](https://datatracker.ietf.org/doc/html/rfc4193 "Unique Local IPv6 Unicast Addresses")

What does it do
----------------

Git-an-IPv6 takes a sequence of IPv6 address snippets and concatenates them behind the fd::/8 prefix.  This produces a non routable address not unlike an RFC 4193 Unique Local Unicast Addresse.  The lowercase hex characters, and the character ":" are processed as input.  Other characters are silently ignored.

Git-an-IPv6 does not have any intelligence about prefix length, it is a simple input-to-output copy with some man-in-the-middle editing.  It does, however, refuse to emit multiple sets of "::" sections.  It shall always emit a legal IPv6 address.  Any deviation from that is a reportable bug.  If the last quartet of digits would otherwise be empty, a "1" is appended.

On input, if the 1st 2 characters independently correspond to "f" and "d", they are also silently dropped.  This allows git-an-IPv6 to be an identity operator on it's own output.  In general, I prefer software with this property.

In practice, the first snippet can be the git-commit-id, which gives a trade off of uniqueness and reproduceability.  Another snipped can be a project subnet.  Although RFC 4193 warns against using well known numbers, users of the same git have a unity of purpose that justifies this.  

License
-------

Use this program as you will.  However, be sure to include the tag "Copyright (c) 2022 Aubrey McIntosh, PhD"

Development process
-------------------

A side purpose for this release is to learn about qmake, and the production of .deb files.  I hand edited git-an-IPv6.pro as produced by qmake, and "make dist" does produce a deb file.

You are invited to submit a pull request with additional items, such as environment variables and files that will help automate more of this process.  In particular, I do not currently know how to configure qmake so that qmake -project will produce the desired .pro file.

Testing
-------

The output does not normally produce an end of line.  By including the character 'n' anywhere in the input stream, the end-of-line character is produced, but the 'n' is dropped from the output.

The envisioned use is in sed commands, e.g. 
 sed "s/42/`git rev-parse --short HEAD`/" dev/control  > $(DEB)/DEBIAN/control



