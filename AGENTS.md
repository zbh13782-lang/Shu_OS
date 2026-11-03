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

### Computer use 与截图

在本项目使用 computer use 操作终端、查看运行结果或为报告截图前，读取 [截图方法与验收要求](skills/os-lab-report/references/screenshots.md)。通过当前可用的 `cua_repl` 及其返回的 API 文档操作真实应用，使用目标应用或标签页的 `getScreenshot()` 获取截图；不可把命令输出绘制成终端图片充当实测截图。

截图应清楚显示题目对应的实际命令、输入和关键输出，保留判断结果所需的上下文；长输出分张连续截图，不缩小到无法阅读，不裁去报错或关键行。原始截图保留，逐张目视核验并建立题号映射。截图与交付源码不一致时，先说明差异；只有已获授权且重跑安全时才重新运行取证。报告页渲染图用于排版验收，不能代替实验运行截图。
