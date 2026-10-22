# 格式保留与预览检查

处理 DOCX 的格式继承、图形保留或中文预览时读取本文件。当前 B 是格式依据；下列旧模板特征仅帮助定位，不是所有实验的固定版式。

## 旧模板特征

本项目实验一 B 为封面、正文与待填占位段落，无表格、页眉页脚。已观察到：

- A4 纵向；上下页边距 2.54 cm，左右 3.175 cm；正文网格行距 312 twips。
- Normal：中文宋体 10.5 pt；西文通常 Calibri，部分段落有宋体直接设置。
- Heading 3：16 pt 加粗，段前段后各 13 pt；行距及保留下一段等来自样式，部分标题直接设置黑体。
- “小标题”：黑体 16 pt 加粗、左对齐。
- 封面首行：22 pt 加粗居中；题目与姓名信息：宋体 16 pt 加粗。
- 封面分隔线为段落内 VML 图形，不一定存在 `word/media` 中，`inline_shapes` 不能完整统计这些装饰。

字体属性可能来自 `docDefaults`、命名样式、段落 `w:pPr/w:rPr`、run `w:rPr`，需一并检查。后续 B 即使名称相同，也先确认实际内容。

## 编辑方式

简单段落修改可用 python-docx；复杂图形或严格保留包结构时，定点修改 ZIP 内的 OOXML 更稳妥。

1. 编辑前给 B 和各包部件记录 SHA-256，记录 `sectPr` 及各角色字体/段落格式原型。
2. 元信息可定点改原 `w:t`；新增段落复制该角色的 `w:pPr` 和相应 run 格式，不整体复制旧段落索引到新实验。
3. 首行“思考”加粗不代表整段问题都应加粗；正文答案也仅按原有范围加粗。
4. 原有封面 VML 分隔线段落保持完整。复杂段落不要直接 `paragraph.text = ...`，以免丢失分 run 格式或图形。
5. 图片使用原文件，添加图片部件、关系和 content type。关系 ID 与 drawing ID 唯一，长宽保持比例；A 的图片关系不能未经映射搬到 B。
6. 新增段落可适度设置 keepNext、keepLines 或孤行控制改善分页，不改变原字体、字号和页边距。过长内容不能全部 keepNext，以免产生大块空白。
7. 比较包部件：正文、图片关系和类型定义变化通常为预期，其他变化需有原因。样式、主题、不相关图形、分节及页眉页脚应无损失。结构一致性不能替代逐页视觉检查。

documents 技能要求的开始标记、模板记录、渲染与校验按当前版本执行。获取其目录和工作区运行时后使用，不硬编码缓存版本、绝对项目目录或旧临时文件。旧实验一次性处理脚本只供借鉴，不能作为新实验生成器。

## 中文预览缺字

典型现象：预览只显示 Latin 字符，中文为空白或方框，但 DOCX 文字和字体设置正常。先核实问题来自渲染环境，而非中文被误删。

在本次临时目录写 fontconfig 配置，让内置 LibreOffice 读取可用中文字体。macOS 存在以下目录时可使用此配置；其他平台选择实际可读的已安装字体：

```xml
<?xml version="1.0"?>
<!DOCTYPE fontconfig SYSTEM "fonts.dtd">
<fontconfig>
  <dir>/System/Library/Fonts</dir>
  <dir>/System/Library/Fonts/Supplemental</dir>
  <alias><family>宋体</family><prefer><family>Songti SC</family></prefer></alias>
  <alias><family>SimSun</family><prefer><family>Songti SC</family></prefer></alias>
  <alias><family>黑体</family><prefer><family>Heiti SC</family></prefer></alias>
  <alias><family>Calibri</family><prefer><family>Arial</family></prefer></alias>
</fontconfig>
```

缓存如需写入，另加 `<cachedir>` 指向本次可写临时目录。不要全局安装字体、改系统配置，或把替代字体写回最终 DOCX。字体替代仅用于本地预览，字宽可能不同于真实宋体/黑体，需要同时核实文档字体属性。

仅对渲染命令设置 `FONTCONFIG_FILE`，以下变量需先按本次环境赋值：

```bash
FONTCONFIG_FILE="$LAB_TASK_TMP/fonts.conf" "$PYTHON_BIN" "$DOCS_SKILL_DIR/render_docx.py" \
  "$REPORT_DOCX" --output_dir "$LAB_TASK_TMP/render-final" --emit_pdf
```

使用工作区依赖的内置 LibreOffice，不切换到用户的桌面 LibreOffice。先用同一环境渲染 B 确认中文恢复，再检查成品每页。输出文件成功不足以证明中文和版式正确。

## 覆盖验证

保留“来源位置 → 原文 → 成品位置”，逐条核对目的、操作、要求、步骤与子题。DOCX 可直接比对文本；PDF 只规范排版引入的换行与空白，不能改命令符号或真实错字。

重新打开成品，检查 ZIP 完整、图片关系有效、原始图片字节与用户文件一致、B 保留部件无意外变化。图片数量相同不证明内容或位置正确。最终逐页检查，包括末页，不只看封面或总览缩略图。
