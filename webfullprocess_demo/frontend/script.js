const form = document.getElementById("messageForm");
const rsp_div = document.getElementById("response");

// 表单的提交
form.addEventListener("submit", async (event) => {
    event.preventDefault(); // 阻止默认行为

    // 获取数据
    const msginput = document.getElementById("message");
    const message = msginput.value;

    const payload = { message };
    try {
        // 发送数据
        const reply = await fetch("http://localhost:12345/api/send-message", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(payload)
        });
        if (!reply.ok) {
            throw new Error(`Error: ${reply.statusText}`);
        }
        const data = await reply.text();
        rsp_div.innerText = data;

    } catch (error) {
        rsp_div.textContent = `Error: ${error.message}`;
    }

});

