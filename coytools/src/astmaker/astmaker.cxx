/**************************************************************************
*
* Copyright (C) 2008, The EROS Group, LLC
* Copyright (C) 2006, Johns Hopkins University.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or
* without modification, are permitted provided that the following
* conditions are met:
*
*   - Redistributions of source code must contain the above 
*     copyright notice, this list of conditions, and the following
*     disclaimer. 
*
*   - Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions, and the following
*     disclaimer in the documentation and/or other materials 
*     provided with the distribution.
*
*   - Neither the names of the copyright holders nor the names of any
*     of any contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission. 
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <string>
#include <cctype>

#include <getopt.h>
#include <libsherpa/INOstream.hxx>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <langinfo.h>

#include "AMlexer.hxx"

using namespace std;
using namespace boost;

bool showparse;			/* set from command line option */
bool showlex;			/* set from command line option */
std::string srcLang;            /* set from command line option */

struct ToMacro {
ToMacro(std::locale const& l) : loc(l) {}
char operator() (char c);
std::locale const& loc;
};

char
ToMacro::operator()(char c)
{
const ctype<char>& ct =  use_facet< ctype<char> >(loc);

if (ct.is(ctype_base::alpha, c))
return std::toupper(c, loc);

if (ct.is(ctype_base::digit, c))
return std::toupper(c, loc);

if (c == '_' || c == '/' || c == '.')
return '_';

return '_';
}

static ToMacro toMacroTransformer(std::locale::classic());

std::string
toMacro(const std::string& s)
{
std::string out = s;
std::transform(out.begin(), out.end(), 
	 out.begin(), toMacroTransformer);

return out;
}

ParseResult *
parse_file(boost::filesystem::path filePath, const boost::filesystem::path& outBase)
{
std::ifstream fin(filePath.string().c_str());

if (!fin.is_open()) {
std::cerr << "Couldn't open input file \""
      << filePath.string()
      << "\"\n",
exit(1);
}

ParseResult *pr = new ParseResult(outBase);

pr->asts.push_back(new AstInfo(dt_leaf, sherpa::LToken("Null")));
pr->asts.push_back(new AstInfo(dt_leaf, sherpa::LToken("AnyGroup")));

AMlexer lexer(fin, filePath.string());
if (showlex)
lexer.setDebug(showlex);

{
extern int amparse(AMlexer *lexer, ParseResult *);
amparse(&lexer, pr);
}

fin.close();

if (lexer.NumErrors() != 0u)
exit(1);

// Re-order aip so that all of the groups fall at the end.
vector<AstInfo *> aipSorted;

for (size_t i = 0; i < pr->asts.size(); i++) {
if (pr->asts[i]->dt != dt_group) {
pr->asts[i]->ndx = aipSorted.size();
aipSorted.push_back(pr->asts[i]);
}
}
for (size_t i = 0; i < pr->asts.size(); i++) {
if (pr->asts[i]->dt == dt_group) {
pr->asts[i]->ndx = aipSorted.size();
aipSorted.push_back(pr->asts[i]);
}
}

pr->asts = aipSorted;

return pr;
}


#define LOPT_SHOWLEX   257   /* Show tokens */
#define LOPT_SHOWPARSE 258   /* Show parse */
#define LOPT_HELP      259   /* Show help */
struct option longopts[] = {
{ "showlex",              0,  0, LOPT_SHOWLEX },
{ "showparse",            0,  0, LOPT_SHOWPARSE },
{ "language",             1,  0, 'l' },
{ "help",                 0,  0, LOPT_HELP },
#if 0
{ "version",              0,  0, 'V' },
#endif
{0,                       0,  0, 0}
};

void
help()
{
std::cerr 
<< "Usage:" << '\n'
<< "  astmaker -h|-s [-o outfilebase] [-l language] file" << '\n'
#if 0
<< "  astmaker -V|--version" << '\n'
#endif
<< "  astmaker --help" << '\n'
<< "where outfilebase is output filename without extension." << '\n'
<< "Debugging options:" << '\n'
<< "  --showlex --showparse" << '\n'
<< "Languages: xmlpp xmldump bitcpp" << endl
;
}

inline unsigned
bincount(unsigned count, unsigned binsize)
{
return (count + (binsize - 1)) / binsize;
}

inline void
set_bit(unsigned char *vec, unsigned bit)
{
vec[bit/8] |= (1u << (bit % 8));
}

inline bool
bit_isSet(unsigned char *vec, unsigned bit)
{
return (vec[bit/8] & (1u << (bit % 8))) ? true : false;
}

void 
emit_one_ast(std::ostream& out, const AstInfo *aip)
{
switch (aip->dt) {
case dt_leaf:
out << "LEAF ";
break;
case dt_group:
out << "GROUP ";
break;
case dt_ast:
out << "AST ";
break;
}
out << aip->nm.str;

if (aip->children->size()) {
out << " =";
for (size_t c = 0; c < aip->children->size(); c++) {
ChildNode *cp = (*aip->children)[c];
out << " "
  << cp->tok.str;
if (cp->ctype != ' ')
out << cp->ctype;
}
}
out << ";"
<< '\n';
}

void 
emit_ast(std::ostream& out, ParseResult *pr, 
 const boost::filesystem::path& outBase)
{
std::vector<AstInfo *>& asts = pr->asts;

for (size_t i = 0; i < asts.size(); i++) {
AstInfo *aip = asts[i];

emit_one_ast(out, aip);
}
}

void
check_asts(ParseResult *pr)
{
std::vector<AstInfo *>& asts = pr->asts;

// First, check that all referenced AST names are defined.

bool allGood = true;

for (size_t i = 0; i < asts.size(); i++) {
AstInfo *aip = asts[i];

for (size_t c = 0; c < aip->children->size(); c++) {
ChildNode *cp = (*aip->children)[c];

bool good = false;

for (size_t j = 0; j < asts.size() && !good; j++) {
AstInfo *aip = asts[j];
if (aip->nm.str == cp->tok.str) {
  good = true;
  cp->tokInfo = aip;
}
}

if (!good) {
std::cerr << cp->tok.loc.asString()
	  << ": undefined AST type \""
	  << cp->tok.str
	  << "\""
	  << std::endl;
allGood = false;
}
}
}

size_t vecSize = bincount(asts.size(), 8);

// Allocate storage for membership and follow vectors, and mark
// self-membership:
for (size_t i = 0; i < asts.size(); i++) {
AstInfo *aip = asts[i];

aip->members = new unsigned char[vecSize];
memset(aip->members, 0, vecSize);
set_bit(aip->members, i);	// everything is a member of itself.

for (size_t c = 0; c < aip->children->size(); c++) {
ChildNode *cp = (*aip->children)[c];
cp->follow = new unsigned char[vecSize];
memset(cp->follow, 0, vecSize);

// group members are members of group
if (aip->dt == dt_group)
set_bit(aip->members, cp->tokInfo->ndx);
}

//    cerr << "Initialized " << aip->tokName() << endl;
}

// Compute transitive membership information:
{
bool changed;
unsigned char *newMembers = new unsigned char[vecSize];

do {
changed = false;

for (size_t i = 0; i < asts.size(); i++) {
AstInfo *aip = asts[i];

//	cerr << "Checking " << aip->tokName() << endl;

memcpy(newMembers, aip->members, vecSize);

for (size_t member = 0; member < asts.size(); member++) {
  if (bit_isSet(aip->members, member)) {
    AstInfo *mip = asts[member];

    //	    cerr << "  Member " << mip->tokName() << endl;

    for(size_t vp = 0; vp < vecSize; vp++) {
      newMembers[vp] |= mip->members[vp];
      if (newMembers[vp] != aip->members[vp])
	changed = true;
    }
  }
}

memcpy(aip->members, newMembers, vecSize);

}

} while(changed);

delete [] newMembers;
}

// Compute follow set information for child nodes:
for (size_t i = 0; i < asts.size(); i++) {
AstInfo *aip = asts[i];

for (size_t c = 0; c < aip->children->size(); c++) {
ChildNode *cp = (*aip->children)[c];

// Following child:
for (size_t fc = c+1; fc < aip->children->size(); fc++) {
ChildNode *fcp = (*aip->children)[fc];

for(size_t vp = 0; vp < vecSize; vp++)
  cp->follow[vp] |= fcp->tokInfo->members[vp];

// If /fc/ is non optional, we are done computing the follow
// set for /c/. Groups are not nullable, so:
if (fcp->ctype == ' ' || fcp->ctype == '+')
  break;
}
}

#if 0
for (size_t c = 0; c < aip->children->size(); c++) {
ChildNode *cp = (*aip->children)[c];

cerr << "AST " << aip->nm.str;
cerr << "[" << c << "]=\"" << cp->tok.str 
   << "\" members:";
for(size_t ast = 0; ast < asts.size(); ast++) {
if (bit_isSet(cp->tokInfo->members, ast))
  cerr << " " << asts[ast]->nm.str;
}
cerr << endl;

cerr << "AST " << aip->nm.str;
cerr << "[" << c << "]=\"" << cp->tok.str 
   << "\" followers:";
for(size_t ast = 0; ast < asts.size(); ast++) {
if (bit_isSet(cp->follow, ast))
  cerr << " " << asts[ast]->nm.str;
}
cerr << endl;
}
#endif

// If the current child is nullable or repeating, and its members
// match its possible successors, the AST is malformed:
for (size_t c = 0; c < aip->children->size(); c++) {
ChildNode *cp = (*aip->children)[c];

if (cp->ctype == ' ') 
continue;

bool conflict = false;

for(size_t vp = 0; !conflict && vp < vecSize; vp++) {
if (cp->tokInfo->members[vp] & cp->follow[vp]) {
  cerr << cp->tok.loc.asString()
       << ": ";
  emit_one_ast(cerr, aip);
  cerr << "    " 
       << "Child " << c
       << " ("
       << cp->tok.str
       << ") is "
       << ((cp->ctype == '+') ? "repeating" : "optional")
       << ", but can be immediately followed by" << endl
       << "    "
       << "something with the same AST type. This is ambiguous."
       << endl;

  conflict = true;
  allGood = false;
}
}
}
}

// Check all repeating children to make sure that their successor
// does not match them.

if (!allGood)
exit(1);
}

bool
transform(std::ostream& outStream, std::istream& inStream, ParseResult* pr)
{
sherpa::INOstream out(outStream);

for(;;) {
char c = inStream.get();
if (c == EOF)
return true;

if (c != '%') {
out << c;
continue;
}

// Looking at start of a replacement token name:
std::ostringstream ss;
ss << c;

do {
c = inStream.get();
if (c == EOF)
return false;
ss << c;
} while(c != '%');

std::string s = ss.str();

// Long if-then-else chain here.
if ( s == "%copyright%" )
out << pr->copyright.str();
else if ( s == "%headerguard%" ) {
std::string hdrGuard = toMacro(pr->outBase.string() + "_HXX");
out << hdrGuard;
}
else if ( s == "%include%" )
out << pr->include.str();
else if ( s == "%namespace%" )
out << pr->nmspace;
else if ( s == "%header%" )
out << pr->header.str();
else if ( s == "%members%" )
out << pr->members.str();
else if ( s == "%c++:astenum%" ) {
std::vector<AstInfo *>& asts = pr->asts;

out << "enum AstType {" << '\n';
out.more();

AstInfo *aip = 0;
for (size_t i = 0; i < asts.size(); i++) {
aip = asts[i];
out << aip->tagName() << "," << '\n';
}
out.less();
out << "};" << '\n' << '\n';

out << "enum { at_NUM_ASTTYPE = " << aip->tagName() << " };" << '\n';
}
}
}

void
do_emit_hdr(std::ostream& outStream, ParseResult *pr)
{
std::vector<AstInfo *>& asts = pr->asts;

std::string hdrGuard = toMacro(pr->outBase.string() + "_HXX");

sherpa::INOstream out(outStream);

out << "#ifndef " << hdrGuard << '\n';
out << "#define " << hdrGuard << '\n' << '\n';
out << pr->copyright.str();
out << '\n';

out << "#include <string>" << '\n';
out << "#include <vector>" << '\n';
out << '\n';

out << pr->include.str();
out << '\n';

if (pr->nmspace.size()) {
out << "namespace " << pr->nmspace << " {" << '\n';
out.more();
}

out << pr->header.str();
out << '\n';
{
out << "enum AstType {" << '\n';
out.more();

AstInfo *aip = 0;
for (size_t i = 0; i < asts.size(); i++) {
aip = asts[i];
out << aip->tagName() << "," << '\n';
}
out.less();
out << "};" << '\n' << '\n';

out << "enum { at_NUM_ASTTYPE = " << aip->tagName() << " };" << '\n';
}
out << '\n';

if (pr->nmspace.size()) {
out.less();
out << "} /* namespace " << pr->nmspace << " */\n";
out << '\n';
}

out << "#ifndef AST_SMART_PTR" << '\n';
out << "#include <boost/shared_ptr.hpp>" << '\n';
out << "#include <boost/enable_shared_from_this.hpp>" << '\n';
out << "#define AST_SMART_PTR(T) boost::shared_ptr<T>" << '\n';
out << "#endif /* AST_SMART_PTR */" << '\n';
out << '\n';
out << "#ifndef AST_LOCATION_TYPE" << '\n';
out << "#include <libsherpa/LexLoc.hxx>" << '\n';
out << "#define AST_LOCATION_TYPE sherpa::LexLoc" << '\n';
out << "#endif /* AST_LOCATION_TYPE */" << '\n';
out << '\n';
out << "#ifndef AST_TOKEN_TYPE" << '\n';
out << "#include <libsherpa/LToken.hxx>" << '\n';
out << "#define AST_TOKEN_TYPE sherpa::LToken" << '\n';
out << "#endif /* AST_TOKEN_TYPE */" << '\n';
out << '\n';
out << "#ifndef AST_GC_THISPTR_SUPERCLASS" << '\n';
out << "#define AST_GC_THISPTR_SUPERCLASS boost::enable_shared_from_this<AST>" << '\n';
out << "#endif /* AST_GC_THISPTR_SUPERCLASS */" << '\n';
out << '\n';

if (pr->nmspace.size()) {
out << "namespace " << pr->nmspace << " {" << '\n';
out.more();
out << '\n';
}

out << "class AST :public AST_GC_THISPTR_SUPERCLASS { " << '\n';
out << "  bool isOneOf(AstType);" << '\n';
out << "public:" << '\n';
out << "  template <class T>" << '\n';
  out << "  struct GCPtr {" << '\n';
  out << "    typedef AST_SMART_PTR(T) Type;" << '\n';
  out << "  };" << '\n';
  out << '\n';
  out << "  AstType        astType;" << '\n';
  out << "  ::std::string    s;" << '\n';
  out << "  AST_LOCATION_TYPE loc;" << '\n';
  out << "  ::std::vector<GCPtr<AST>::Type > children;" << '\n';
  out << '\n';

  out << pr->members.str();
  out << '\n';

  out << "  AST(const AstType at = at_Null);" << '\n';
  out << "  // for literals:" << '\n';
  out << "  AST(const AstType at, const AST_TOKEN_TYPE& tok);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2," << '\n';
  out << "      GCPtr<AST>::Type child3);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2," << '\n';
  out << "      GCPtr<AST>::Type child3," << '\n';
  out << "      GCPtr<AST>::Type child4);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2," << '\n';
  out << "      GCPtr<AST>::Type child3," << '\n';
  out << "      GCPtr<AST>::Type child4," << '\n';
  out << "      GCPtr<AST>::Type child5);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2," << '\n';
  out << "      GCPtr<AST>::Type child3," << '\n';
  out << "      GCPtr<AST>::Type child4," << '\n';
  out << "      GCPtr<AST>::Type child5," << '\n';
  out << "      GCPtr<AST>::Type child6);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2," << '\n';
  out << "      GCPtr<AST>::Type child3," << '\n';
  out << "      GCPtr<AST>::Type child4," << '\n';
  out << "      GCPtr<AST>::Type child5," << '\n';
  out << "      GCPtr<AST>::Type child6," << '\n';
  out << "      GCPtr<AST>::Type child7);" << '\n';
  out << "  AST(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "      GCPtr<AST>::Type child1," << '\n';
  out << "      GCPtr<AST>::Type child2," << '\n';
  out << "      GCPtr<AST>::Type child3," << '\n';
  out << "      GCPtr<AST>::Type child4," << '\n';
  out << "      GCPtr<AST>::Type child5," << '\n';
  out << "      GCPtr<AST>::Type child6," << '\n';
  out << "      GCPtr<AST>::Type child7," << '\n';
  out << "      GCPtr<AST>::Type child8);" << '\n';
  out << "  ~AST();" << '\n';
  out << '\n';
  out << "  // Helper quasi-constructors" << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at = at_Null)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_TOKEN_TYPE& tok)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, tok);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       GCPtr<AST>::Type child1)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2," << '\n';
  out << "       const GCPtr<AST>::Type child3)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2," << '\n';
  out << "                       child3);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2," << '\n';
  out << "       const GCPtr<AST>::Type child3," << '\n';
  out << "       const GCPtr<AST>::Type child4)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2," << '\n';
  out << "                       child3, child4);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2," << '\n';
  out << "       const GCPtr<AST>::Type child3," << '\n';
  out << "       const GCPtr<AST>::Type child4," << '\n';
  out << "       const GCPtr<AST>::Type child5)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2," << '\n';
  out << "                       child3, child4, child5);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2," << '\n';
  out << "       const GCPtr<AST>::Type child3," << '\n';
  out << "       const GCPtr<AST>::Type child4," << '\n';
  out << "       const GCPtr<AST>::Type child5," << '\n';
  out << "       const GCPtr<AST>::Type child6)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2," << '\n';
  out << "                       child3, child4, child5," << '\n';
  out << "                       child6);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2," << '\n';
  out << "       const GCPtr<AST>::Type child3," << '\n';
  out << "       const GCPtr<AST>::Type child4," << '\n';
  out << "       const GCPtr<AST>::Type child5," << '\n';
  out << "       const GCPtr<AST>::Type child6," << '\n';
  out << "       const GCPtr<AST>::Type child7)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2," << '\n';
  out << "                       child3, child4, child5," << '\n';
  out << "                       child6, child7);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static inline GCPtr<AST>::Type" << '\n';
  out << "  make(const AstType at, const AST_LOCATION_TYPE &loc," << '\n';
  out << "       const GCPtr<AST>::Type child1," << '\n';
  out << "       const GCPtr<AST>::Type child2," << '\n';
  out << "       const GCPtr<AST>::Type child3," << '\n';
  out << "       const GCPtr<AST>::Type child4," << '\n';
  out << "       const GCPtr<AST>::Type child5," << '\n';
  out << "       const GCPtr<AST>::Type child6," << '\n';
  out << "       const GCPtr<AST>::Type child7," << '\n';
  out << "       const GCPtr<AST>::Type child8)" << '\n';
  out << "  {" << '\n';
  out << "    AST *ast = new AST(at, loc, child1, child2," << '\n';
  out << "                       child3, child4, child5," << '\n';
  out << "                       child6, child7, child8);" << '\n';
  out << "    return GCPtr<AST>::Type(ast);" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << '\n';
  out << "  const GCPtr<AST>::Type" << '\n';
  out << "  child(size_t i) const" << '\n';
  out << "  {" << '\n';
  out << "    return children[i];" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  GCPtr<AST>::Type&" << '\n';
  out << "  child(size_t i)" << '\n';
  out << "  {" << '\n';
  out << "    return children[i];" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  void addChild(GCPtr<AST>::Type cld);" << '\n';
  out << "  ::std::string getTokenString();" << '\n';
  out << '\n';
  out << "  void" << '\n';
  out << "  addChildrenFrom(GCPtr<AST>::Type other)" << '\n';
  out << "  {" << '\n';
  out << "    for(size_t i = 0; i < other->children.size(); i++)" << '\n';
  out << "      addChild(other->child(i));" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  static const char *tagName(const AstType at);" << '\n';
  out << "  static const char *nodeName(const AstType at);" << '\n';
  out << "  static const char *printName(const AstType at);" << '\n';
  out << '\n';
  out << "  inline const char *tagName() const" << '\n';
  out << "  { return tagName(astType); }" << '\n';
  out << '\n';
  out << "  inline const char *nodeName() const" << '\n';
  out << "  { return nodeName(astType); }" << '\n';
  out << '\n';
  out << "  inline const char *printName() const" << '\n';
  out << "  { return printName(astType); }" << '\n';
  out << '\n';
  out << "  bool isMemberOfType(AstType) const;" << '\n';
  out << "  bool isValid() const;" << '\n';
  out << "};" << '\n' << '\n';

  if (pr->nmspace.size()) {
    out.less();
    out << "} /* namespace " << pr->nmspace << " */" << '\n';
    out << '\n';
  }

  out << '\n' << "#endif /* " << hdrGuard << " */" << '\n';
}

void
emit_hdr(ParseResult *pr)
{
  boost::filesystem::path hdrPath = 
    boost::filesystem::change_extension(pr->outBase, ".hxx");

  std::ofstream out(hdrPath.string().c_str(),
		    std::ios_base::out|std::ios_base::trunc);

  if (!out.is_open()) {
    std::cerr << "Couldn't open output file \""
	      << hdrPath.string()
	      << "\" -- "
	      << strerror(errno)
	      << "\n";
    exit(1);
  }

  do_emit_hdr(out, pr);

  out.close();
}

void
emit_src(ParseResult *pr)
{
  std::vector<AstInfo *>& asts = pr->asts;
  boost::filesystem::path srcPath = boost::filesystem::change_extension(pr->outBase, ".cxx");

  std::ofstream out(srcPath.string().c_str(),
		    std::ios_base::out|std::ios_base::trunc);

  if (!out.is_open()) {
    std::cerr << "Couldn't open output file \""
	      << srcPath.string()
	      << "\" -- "
	      << strerror(errno)
	      << "\n";
    exit(1);
  }

  out << pr->copyright.str();
  out << '\n';

  out << "#include <stdlib.h>" << '\n';
  out << "#include <dirent.h>" << '\n';
  out << "#include <fstream>" << '\n';
  out << "#include <iostream>" << '\n';
  out << "#include <string>" << '\n';

  out << "#include \""
      << pr->outBase.leaf()
      << ".hxx\"" << '\n';

  out << '\n';

  out << pr->sourceTop.str();
  out << '\n';

  if (pr->nmspace.size()) {
    out << "namespace " << pr->nmspace << " {" << '\n';
    out << '\n';
  }

  out << '\n';
  out << "AST::~AST()" << '\n';
  out << "{" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';
 
  out << "AST::AST(const AstType at, const AST_TOKEN_TYPE& tok)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = tok.loc;" << '\n';
  out << "  s = tok.str;" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2," << '\n';
  out << "         GCPtr<AST>::Type child3)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << "  addChild(child3);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2," << '\n';
  out << "         GCPtr<AST>::Type child3," << '\n';
  out << "         GCPtr<AST>::Type child4)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << "  addChild(child3);" << '\n';
  out << "  addChild(child4);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2," << '\n';
  out << "         GCPtr<AST>::Type child3," << '\n';
  out << "         GCPtr<AST>::Type child4," << '\n';
  out << "         GCPtr<AST>::Type child5)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << "  addChild(child3);" << '\n';
  out << "  addChild(child4);" << '\n';
  out << "  addChild(child5);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2," << '\n';
  out << "         GCPtr<AST>::Type child3," << '\n';
  out << "         GCPtr<AST>::Type child4," << '\n';
  out << "         GCPtr<AST>::Type child5," << '\n';
  out << "         GCPtr<AST>::Type child6)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << "  addChild(child3);" << '\n';
  out << "  addChild(child4);" << '\n';
  out << "  addChild(child5);" << '\n';
  out << "  addChild(child6);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2," << '\n';
  out << "         GCPtr<AST>::Type child3," << '\n';
  out << "         GCPtr<AST>::Type child4," << '\n';
  out << "         GCPtr<AST>::Type child5," << '\n';
  out << "         GCPtr<AST>::Type child6," << '\n';
  out << "         GCPtr<AST>::Type child7)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << "  addChild(child3);" << '\n';
  out << "  addChild(child4);" << '\n';
  out << "  addChild(child5);" << '\n';
  out << "  addChild(child6);" << '\n';
  out << "  addChild(child7);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "AST::AST(const AstType at, const AST_LOCATION_TYPE& _loc," << '\n';
  out << "         GCPtr<AST>::Type child1," << '\n';
  out << "         GCPtr<AST>::Type child2," << '\n';
  out << "         GCPtr<AST>::Type child3," << '\n';
  out << "         GCPtr<AST>::Type child4," << '\n';
  out << "         GCPtr<AST>::Type child5," << '\n';
  out << "         GCPtr<AST>::Type child6," << '\n';
  out << "         GCPtr<AST>::Type child7," << '\n';
  out << "         GCPtr<AST>::Type child8)" << '\n';
  out << "{" << '\n';
  out << "  astType = at;" << '\n';
  out << "  loc = _loc;" << '\n';
  out << "  addChild(child1);" << '\n';
  out << "  addChild(child2);" << '\n';
  out << "  addChild(child3);" << '\n';
  out << "  addChild(child4);" << '\n';
  out << "  addChild(child5);" << '\n';
  out << "  addChild(child6);" << '\n';
  out << "  addChild(child8);" << '\n';
  out << pr->construct.str();
  out << "}" << '\n';
  out << '\n';

  out << "::std::string" << '\n';
  out << "AST::getTokenString()" << '\n';
  out << "{" << '\n';
  out << "  return s;" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "void" << '\n'; 
  out << "AST::addChild(GCPtr<AST>::Type cld)" << '\n';
  out << "{" << '\n';
  out << "  children.push_back(cld);" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "const char *" << '\n';
  out << "AST::tagName(const AstType at)" << '\n';
  out << "{" << '\n';
  out << "  switch(at) {" << '\n';

  for (size_t i = 0; i < asts.size(); i++) {
    AstInfo *aip = asts[i];
    out << "  case " << aip->tagName() << ":" << '\n';
    out << "    return \"" << aip->tagName() << "\";" << '\n';
  }

  out << "  default:" << '\n';
  out << "    return \"<unknown>\";" << '\n';
  out << "  }" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "const char *" << '\n';
  out << "AST::nodeName(const AstType at)" << '\n';
  out << "{" << '\n';
  out << "  switch(at) {" << '\n';

  for (size_t i = 0; i < asts.size(); i++) {
    AstInfo *aip = asts[i];
    out << "  case " << aip->tagName() << ":" << '\n';
    out << "    return \"" << aip->nm.str << "\";" << '\n';
  }

  out << "  default:" << '\n';
  out << "    return \"<unknown>\";" << '\n';
  out << "  }" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "const char *" << '\n';
  out << "AST::printName(const AstType at)" << '\n';
  out << "{" << '\n';
  out << "  switch(at) {" << '\n';

  for (size_t i = 0; i < asts.size(); i++) {
    AstInfo *aip = asts[i];
    out << "  case " << aip->tagName() << ":" << '\n';
    out << "    return \"" << aip->printName << "\";" << '\n';
  }

  out << "  default:" << '\n';
  out << "    return \"<unknown>\";" << '\n';
  out << "  }" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "#define ISSET(v,b) ((v)[((b)/8)] & (1u << ((b)%8)))" << '\n';
  out << '\n';

  out << "void" << '\n';
  out << "astChTypeError(const AST &myAst, const AstType exp_at," << '\n';
  out << "               const AstType act_at, size_t child)" << '\n';
  out << "{" << '\n';
  out << "  ::std::cerr << myAst.loc.asString() << \": \" << myAst.tagName();" << '\n';
  out << "  ::std::cerr << \" has incompatible Child# \" << child;" << '\n';
  out << "  ::std::cerr << \". Expected \" << AST::tagName(exp_at) << \", \"; " << '\n';
  out << "  ::std::cerr << \"Obtained \" << AST::tagName(act_at) << \".\" << ::std::endl;" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << "void" << '\n';
  out << "astChNumError(const AST &myAst, const size_t exp_ch," << '\n';
  out << "               const size_t act_ch)" << '\n';
  out << "{" << '\n';
  out << "  ::std::cerr << myAst.loc.asString() << \": \" << myAst.tagName();" << '\n';
  out << "  ::std::cerr << \" has wrong number of children. \";" << '\n';
  out << "  ::std::cerr << \"Expected \" << exp_ch << \", \";" << '\n';
  out << "  ::std::cerr << \"Obtained \" << act_ch << \".\" << ::std::endl;" << '\n';
  out << "}" << '\n';
  out << '\n';

#ifdef GENERATE_LIMITED_AST_WALKER
/******************************************************************/
//  AST Walker:
//    The following code will generate a limited ASTWalker.
//    It is very obvious that the following 
//    code works only for a special case where *,+, and ? only appear
//    on the extreme right. Generating a general purpose walker 
//    is also trivial.
/******************************************************************/
  
  out << "void" << '\n';
  out << "astWalker(GCPtr<AST>::Type ast)" << '\n';
  out << "{" << '\n';
  out << "  size_t c;" << '\n';
  out << "  switch(ast->astType) {" << '\n';
  
  for (size_t i = 0; i < asts.size(); i++) {
    AstInfo *aip = asts[i];
    
    switch(aip->dt) {
    case dt_leaf:
      out << "  case " << aip->tagName() << ":" << '\n';
      out << "    // leaf AST:" << '\n';
      break;
    case dt_ast:			// normal ast type
      out << "  case " << aip->tagName() << ":" << '\n';
      for (size_t c = 0, cc =0; c < aip->children->size(); c++) {
	ChildNode *cp = (*aip->children)[c];

	switch(cp->ctype) {
	case ' ':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << '\n';
	    out << "    astWalker(ast->child(" << cc << "));" << '\n';
	    out << '\n';
	    cc++;
	    break;
	  }
	case '*':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << "*" << '\n';
	    out << "    c = " << cc << ";" << '\n';
	    out << "    while (c < ast->children.size()) {" << '\n';
	    out << "      astWalker(ast->child(c));" << '\n';
	    out << "      c++;" << '\n';
	    out << "    }" << '\n';
	    out << '\n';
	    cc++;
	    break;
	  }
	case '+':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << "+" << '\n';
	    out << "    c = " << cc << ";" << '\n';
	    out << "    while (c < ast->children.size()) {" << '\n';
	    out << "      astWalker(ast->child(c));" << '\n';
	    out << "      c++;" << '\n';
	    out << "    }" << '\n';
	    out << '\n';
	    cc++;
	    break;
	  }
	case '?':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << "?" << '\n';
	    out << "    if (ast->children.size() > " << cc << ") {" << '\n';
	    out << "      astWalker(ast->child(" << cc << "));" << '\n';
	    c++;
	    out << "    }" << '\n';
	    out << '\n';
	    break;
	  }
	default:
	  break;
	}
      }

      break;
    case dt_group:			// grouping pseudo-ast
      out << "  // group AST" << aip->tagName() << " gets default" << '\n';
      break;
    default:
      break;
    }
    out << "    break;" << '\n';
    out << '\n';
  }
  
  out << "  default:" << '\n';
  out << "    ;" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "}" << '\n';
  out << '\n';

#endif /* GENERATE_LIMITED_AST_WALKER */

  out << "static const unsigned char *astMembers[] = {" << '\n';

  {
    size_t vecSize = bincount(asts.size(), 8);

    for (size_t i = 0; i < asts.size(); i++) {
      AstInfo *aip = asts[i];
      char comma = ((i+1) == asts.size()) ? ' ' : ',';
      out << "  (unsigned char *)\"";
      for (size_t b = 0; b < vecSize; b++)
	out << "\\x" << std::setfill('0') << std::setw(2) << std::hex 
	    << ((unsigned long)aip->members[b]) 
	    << std::setfill(' ') << std::setw(0) << std::dec;
      out << "\"" << comma << " // " << aip->tagName() << '\n';
    }
  }
  out << "};" << '\n';
  out << '\n';

  out << "bool" << '\n';
  out << "AST::isMemberOfType(AstType ty) const" << '\n';
  out << "{" << '\n';
  out << "  return ISSET(astMembers[ty], astType) ? true : false;";
  out << "}" << '\n';
  out << '\n';

  out << "bool" << '\n';
  out << "AST::isValid() const" << '\n';
  out << "{" << '\n';
  out << "  size_t c;" << '\n';
  out << "  size_t specNdx;" << '\n';
  out << "  bool errorsPresent = false;" << '\n';
  out << '\n';
  out << "  for (c = 0; c < children.size(); c++) {" << '\n';
  out << "    if (!child(c)->isValid())" << '\n';
  out << "      errorsPresent = true;" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  c = 0;" << '\n';
  out << "  specNdx = 0;" << '\n';
  out << '\n';
  out << "  switch(astType) {" << '\n';

  for (size_t i = 0; i < asts.size(); i++) {
    AstInfo *aip = asts[i];

    switch(aip->dt) {
    case dt_leaf:
      out << "  case " << aip->tagName() << ":";
      out << " // leaf AST:" << '\n';
      out << "    if(children.size() != 0) {" << '\n';
      out << "      astChNumError(*this, 0, children.size());" << '\n';
      out << "      errorsPresent = true;" << '\n';
      out << "    }" << '\n';
      break;
    case dt_ast:			// normal ast type
      out << "  case " << aip->tagName() << ":";
      out << " // normal AST:" << '\n';
      for (size_t c = 0; c < aip->children->size(); c++) {
	ChildNode *cp = (*aip->children)[c];

	switch(cp->ctype) {
	case ' ':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << '\n';
	    out << "    if(c >= children.size()) {" << '\n';
	    out << "      astChNumError(*this, c+1, children.size());" << '\n';
	    out << "      errorsPresent = true;" << '\n';
	    out << "      break;" << '\n';
	    out << "    }" << '\n';

	    out << "    if (!ISSET(astMembers[" 
		<< cp->tokInfo->tagName() 
		<< "], child(c)->astType)) {" << '\n';
	    out << "      astChTypeError(*this, " << cp->tokInfo->tagName()
		<< ", child(c)->astType, c);" << '\n';
	    out << "      errorsPresent = true;" << '\n';
	    out << "    }" << '\n';
	    out << "    c++;" << '\n';
	    out << '\n';
	    break;
	  }
	case '*':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << "*" << '\n';
	    out << "    while (c < children.size()) {" << '\n'
		<< "      if (!ISSET(astMembers[" 
		<< cp->tokInfo->tagName()
		<< "], child(c)->astType))"
		<< '\n';
	    out << "        astChTypeError(*this, " << cp->tokInfo->tagName()
		<< ", child(c)->astType, c);" << '\n';
	    out << "      c++;" << '\n';
	    out << "    }" << '\n';
	    out << '\n';
	    break;
	  }
	case '+':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << "+" << '\n';
	    out << "    if(c >= children.size()) {" << '\n';
	    out << "      astChNumError(*this, c+1, children.size());" << '\n';
	    out << "      errorsPresent = true;" << '\n';
	    out << "      break;" << '\n';
	    out << "    }" << '\n';

	    out << "    if (!ISSET(astMembers[" 
		<< cp->tokInfo->tagName() 
		<< "], child(c)->astType)) {" << '\n';
	    out << "      astChTypeError(*this, " << cp->tokInfo->tagName()
		<< ", child(c)->astType, " << c << ");" << '\n';
	    out << "      errorsPresent = true;" << '\n';
	    out << "    }" << '\n';

	    out << "    while (c < children.size()) {" << '\n'
		<< "      if (!ISSET(astMembers[" 
		<< cp->tokInfo->tagName()
		<< "], child(c)->astType))"
		<< '\n';
	    out << "        astChTypeError(*this, " << cp->tokInfo->tagName()
		<< ", child(c)->astType, c);" << '\n';
	    out << "      c++;" << '\n';
	    out << "    }" << '\n';
	    out << '\n';
	    break;
	  }
	case '?':
	  {
	    out << "    // match " << cp->tokInfo->tagName() << "?" << '\n';
	    out << "    if ((c < children.size()) && ISSET(astMembers[" 
		<< cp->tokInfo->tagName() 
		<< "], child(c)->astType)"
		<< ")" << '\n';
	    out << "      c++;" << '\n';
	    out << '\n';
	    break;
	  }
	default:
	  break;
	}
      }

      out << "    if(c != children.size()) {" << '\n';
      out << "      astChNumError(*this, c, children.size());" << '\n';
      out << "      errorsPresent = true;" << '\n';
      out << "    }" << '\n';
      
      break;
    case dt_group:			// grouping pseudo-ast
      out << "  // group AST" << aip->tagName() << " gets default" << '\n';
      break;
    default:
      break;
    }
    out << "    break;" << '\n';
    out << '\n';
  }
  
  out << "  default:" << '\n';
  out << "    errorsPresent = true;" << '\n';
  out << "  }" << '\n';
  out << '\n';
  out << "  return !errorsPresent;" << '\n';
  out << "}" << '\n';
  out << '\n';

  out << pr->source.str();
  out << '\n';

  if (pr->nmspace.size()) {
    out << "} /* namespace " << pr->nmspace << " */" << '\n';
    out << '\n';
  }

  out.close();
}

int
main(int argc, char *argv[]) 
{
  int c;
  extern int optind;
  int opterr = 0;

  bool wantHdr = false;
  bool wantSrc = false;

  boost::filesystem::path outputFileName;

#if 0
  // Make sure that we are running in a UNICODE locale:
  setlocale(LC_ALL, "");
  if (strcmp("UTF-8", nl_langinfo(CODESET)) != 0) {
    std::cerr
      << "We appear to be running in the non-unicode locale "
      << nl_langinfo(CODESET)
      << ".\n"
      << "The AstMaker compiler will only operate correctly "
      << "in a unicode locale.\n";
    exit(1);
  }
#endif

  while ((c = getopt_long(argc, argv, 
			  "l:o:hs",
			  longopts, 0
		     )) != -1) {
    switch(c) {

    case LOPT_SHOWPARSE:
      showparse = true;
      break;

    case LOPT_SHOWLEX:
      showlex = true;
      break;

    case LOPT_HELP: 
      {
	help();
	exit(1);
      }

    case 'l':
      {
        if (!srcLang.empty()) {
          std::cerr << "astmaker: output language should be specified at most once.\n";
          help();
          exit(1);
        }
        srcLang = optarg;
        break;
      }

    case 'h': 
      {
	wantHdr = true;
	break;
      }

    case 's': 
      {
	wantSrc = true;
	break;
      }

    case 'o':
      outputFileName = optarg;
      break;

    default:
      opterr++;
    }
  }
  
  argc -= optind;
  argv += optind;
  
  if (argc == 0)
    opterr++;

  if (opterr || argc != 1) {
    std::cerr << "Usage: Try astmaker --help" << std::endl;
    exit(0);
  }

  if (outputFileName.empty())
    outputFileName = argv[0];

  boost::filesystem::path outBase = 
    outputFileName.branch_path() / basename(outputFileName);

  ParseResult *pr = parse_file(boost::filesystem::path(argv[0]), outBase);

  check_asts(pr);

  //  emit_ast(pr, outBase);
  if (wantHdr) emit_hdr(pr);
  if (wantSrc) emit_src(pr);

  exit(0);
}
