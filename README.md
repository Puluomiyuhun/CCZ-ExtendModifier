# CCZ-ExtendModifier

曹操传 Mod《楚汉韩信传》扩展系统数据编辑器。

## 用途

图形化编辑 [CCZ-ExtendData](https://github.com/Puluomiyuhun/CCZ-ExtendData) 插件所使用的 `.e5` 二进制数据文件，支持离线文件编辑和运行时内存热改两种模式。

## 功能模块

| 面板 | 数据文件 | 说明 |
|---|---|---|
| 特技（TEJI） | `Effect.e5` | 编辑 1024 个人物的最多 256 个特技槽（ID、等级、经验、回合数） |
| 策略（MEFF） | `MeffStudy.e5` | 编辑 1024 个人物的最多 32 个策略槽（ID、使用次数） |
| 锻造（FORGE） | `Forge.e5` | 编辑 1024 条锻造配方（名称、材料、产物、价格、次数） |
| 道具（DAOJU） | `Item.e5` / `Itemmsg.e5` | 编辑道具名称、种类、属性、描述 |

## 工作模式

- **文件模式**（默认）：直接读写磁盘上的 `.e5` 文件，用于离线配置
- **内存模式**：通过菜单「模式」切换，枚举查找游戏窗口（类名前缀 `SOUSOU`），实时读写游戏进程内存

## 开发环境配置

### 环境要求

- Visual Studio 2019 或更高版本
- 工作负载：**使用 C++ 的桌面开发**（含 MFC）
- 目标平台：x86（32位）

### 编译步骤

1. 克隆仓库

```bash
git clone https://github.com/Puluomiyuhun/CCZ-ExtendModifier.git
```

2. 用 Visual Studio 打开 `ExtendModifier.sln`
3. 选择 `Release | x86` 配置
4. 生成解决方案（F7）

### 首次使用

编译完成后，在 `Release/` 目录下运行 `ExtendModifier.exe`，然后通过「文件 > 打开」选择游戏目录中的对应 `.e5` 文件进行编辑。
