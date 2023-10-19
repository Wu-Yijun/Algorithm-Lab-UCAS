
const kMyGitHubRepoPath = "https://github.com/Wu-Yijun/Algorithm-Lab-UCAS/";

function onCopy(elem) {
    val = elem.parentNode.parentNode.previousElementSibling.firstChild
    window.getSelection().selectAllChildren(val);
    document.execCommand("Copy");
    window.getSelection().removeAllRanges();
}

function GotoIndex() {
    if (window.event.ctrlKey)
        window.open('../', '_blank');
    else
        window.location.href = '../';
}
function Goback() {
    window.history.back();
}
function ViewCode(url) {
    if (window.event.ctrlKey)
        window.open(kMyGitHubRepoPath + "blob/master/" + url, '_blank');
    else
        window.location.href = kMyGitHubRepoPath + "blob/master/" + url;
}
function RefreshPage() {
    window.location.reload();
}