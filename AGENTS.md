<!-- CODEGRAPH_START -->
## CodeGraph

In repositories indexed by CodeGraph (a `.codegraph/` directory exists at the repo root), reach for it BEFORE grep/find or reading files when you need to understand or locate code:

- **MCP tool** (when available): `codegraph_explore` answers most code questions in one call — the relevant symbols' verbatim source plus the call paths between them, including dynamic-dispatch hops grep can't follow. Name a file or symbol in the query to read its current line-numbered source. If it's listed but deferred, load it by name via tool search.
- **Shell** (always works): `codegraph explore "<symbol names or question>"` prints the same output.

If there is no `.codegraph/` directory, skip CodeGraph entirely — indexing is the user's decision.
<!-- CODEGRAPH_END -->

## 操作系统实验与报告

当用户要求在本项目中编写或修改操作系统实验代码、使用已授权的实验服务器，或根据参考报告 A、模板 B 和截图填写实验报告时，先读取并使用 [os-lab-report skill](skills/os-lab-report/SKILL.md)。该技能适用于实验三及后续类似任务，不用于其他无关工作。

用户提供本次实验材料并要求完成代码或报告，即按技能开始工作。保留已确认的姓名、学号、基础 C 写法和报告格式约定，新要求优先。服务器连接方法与凭据路径见技能引用，私钥位于技能内排除版本管理的 `.local/ssh/`，不读取或展示私钥内容。skill 存放在项目内，无需依赖此前聊天历史、全局技能安装或旧临时脚本。
