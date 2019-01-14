## SymFun
The SCC::SymFun class allows one to specify a scalar function of any specified number of variables symbolically, i.e. using a string. In addition, the specification can include symbolic constants. 

Currently SCC::SymFun instances use static data member functions so SCC:SymFun instances are not thread safe. When executing a program that uses an SCC::SymFun instance, care should be taken that the evaluation of  SCC::SymFun instances should only be done by a single thread.  
 
### Prerequisites

GNU make

### Versioning

Release : 18.08.31

### Authors

Chris Anderson

### License

GPLv3  For a copy of the GNU General Public License see <http://www.gnu.org/licenses/>.

### Acknowledgements















