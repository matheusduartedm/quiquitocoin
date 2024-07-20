# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libquiquitocoin_cli*         | RPC client functionality used by *quiquitocoin-cli* executable |
| *libquiquitocoin_common*      | Home for common functionality shared by different executables and libraries. Similar to *libquiquitocoin_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libquiquitocoin_consensus*   | Stable, backwards-compatible consensus functionality used by *libquiquitocoin_node* and *libquiquitocoin_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libquiquitocoinconsensus*    | Shared library build of static *libquiquitocoin_consensus* library |
| *libquiquitocoin_kernel*      | Consensus engine and support library used for validation by *libquiquitocoin_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libquiquitocoinqt*           | GUI functionality used by *quiquitocoin-qt* and *quiquitocoin-gui* executables |
| *libquiquitocoin_ipc*         | IPC functionality used by *quiquitocoin-node*, *quiquitocoin-wallet*, *quiquitocoin-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libquiquitocoin_node*        | P2P and RPC server functionality used by *quiquitocoind* and *quiquitocoin-qt* executables. |
| *libquiquitocoin_util*        | Home for common functionality shared by different executables and libraries. Similar to *libquiquitocoin_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libquiquitocoin_wallet*      | Wallet functionality used by *quiquitocoind* and *quiquitocoin-wallet* executables. |
| *libquiquitocoin_wallet_tool* | Lower-level wallet functionality used by *quiquitocoin-wallet* executable. |
| *libquiquitocoin_zmq*         | [ZeroMQ](../zmq.md) functionality used by *quiquitocoind* and *quiquitocoin-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libquiquitocoin_consensus* and *libquiquitocoin_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libquiquitocoin_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libquiquitocoin_node* code lives in `src/node/` in the `node::` namespace
  - *libquiquitocoin_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libquiquitocoin_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libquiquitocoin_util* code lives in `src/util/` in the `util::` namespace
  - *libquiquitocoin_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

quiquitocoin-cli[quiquitocoin-cli]-->libquiquitocoin_cli;

quiquitocoind[quiquitocoind]-->libquiquitocoin_node;
quiquitocoind[quiquitocoind]-->libquiquitocoin_wallet;

quiquitocoin-qt[quiquitocoin-qt]-->libquiquitocoin_node;
quiquitocoin-qt[quiquitocoin-qt]-->libquiquitocoinqt;
quiquitocoin-qt[quiquitocoin-qt]-->libquiquitocoin_wallet;

quiquitocoin-wallet[quiquitocoin-wallet]-->libquiquitocoin_wallet;
quiquitocoin-wallet[quiquitocoin-wallet]-->libquiquitocoin_wallet_tool;

libquiquitocoin_cli-->libquiquitocoin_util;
libquiquitocoin_cli-->libquiquitocoin_common;

libquiquitocoin_common-->libquiquitocoin_consensus;
libquiquitocoin_common-->libquiquitocoin_util;

libquiquitocoin_kernel-->libquiquitocoin_consensus;
libquiquitocoin_kernel-->libquiquitocoin_util;

libquiquitocoin_node-->libquiquitocoin_consensus;
libquiquitocoin_node-->libquiquitocoin_kernel;
libquiquitocoin_node-->libquiquitocoin_common;
libquiquitocoin_node-->libquiquitocoin_util;

libquiquitocoinqt-->libquiquitocoin_common;
libquiquitocoinqt-->libquiquitocoin_util;

libquiquitocoin_wallet-->libquiquitocoin_common;
libquiquitocoin_wallet-->libquiquitocoin_util;

libquiquitocoin_wallet_tool-->libquiquitocoin_wallet;
libquiquitocoin_wallet_tool-->libquiquitocoin_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class quiquitocoin-qt,quiquitocoind,quiquitocoin-cli,quiquitocoin-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libquiquitocoin_wallet* and *libquiquitocoin_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libquiquitocoin_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libquiquitocoin_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libquiquitocoin_common* should serve a similar function as *libquiquitocoin_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libquiquitocoin_util* and *libquiquitocoin_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for quiquitocoin-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libquiquitocoin_kernel* is not supposed to depend on *libquiquitocoin_common*, only *libquiquitocoin_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libquiquitocoin_kernel* should only depend on *libquiquitocoin_util* and *libquiquitocoin_consensus*.

- The only thing that should depend on *libquiquitocoin_kernel* internally should be *libquiquitocoin_node*. GUI and wallet libraries *libquiquitocoinqt* and *libquiquitocoin_wallet* in particular should not depend on *libquiquitocoin_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libquiquitocoin_consensus*, *libquiquitocoin_common*, and *libquiquitocoin_util*, instead of *libquiquitocoin_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libquiquitocoinqt*, *libquiquitocoin_node*, *libquiquitocoin_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libquiquitocoin_node* to *libquiquitocoin_kernel* as part of [The libquiquitocoinkernel Project #24303](https://github.com/quiquitocoin/quiquitocoin/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/quiquitocoin/quiquitocoin/issues/15732)
